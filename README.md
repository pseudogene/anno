Contents
--------

[Introduction](#Introduction)

[Quick tutorial](#Quick_tutorial)

[Where to Find It](#Where_to_Find_It)

[Usage](#Usage)

-   [Command line](#Command_line)
-   [Input files](#Input_files)
-   [Parameters](#Parameters)

[Example](#Example)

-   [Built-in example](#Built-in_example)

[Contact](#Contact)

* * * * *

Introduction
============

TabAnno is short for "Tab-delimited file Annotation", it is used for annotate variety of genetic variants stored in tab-delimited files. 
Our goal is to provide abundant information for genetic variants efficiently.
Some annotation software output only one annotation per variant, while TabAnno
will provide annotations to all transcripts. TabAnno supports
various file format: VCF file, plain text file, plink association output file
and
[EPACTS](http://genome.sph.umich.edu/wiki/EPACTS "http://genome.sph.umich.edu/wiki/EPACTS")
file.

Quick tutorial
==============

You have an input file in VCF format, and your goal is to annotate it
using refFlat gene definition. Then you just need the following command:

     anno -i input.vcf -o output.vcf -r hs37d5.fa -g refFlat_hg19.txt.gz -p priority.txt -c codon.txt

Required files:

-   [hs37d5.fa](http://www.sph.umich.edu/csg/zhanxw/software/anno/resources/hs37d5.fa "http://www.sph.umich.edu/csg/zhanxw/software/anno/resources/hs37d5.fa")
    Reference genome in NCBI build 37 (you also need to download
    [hs37d5.fai](http://www.sph.umich.edu/csg/zhanxw/software/anno/resources/hs37d5.fa.fai "http://www.sph.umich.edu/csg/zhanxw/software/anno/resources/hs37d5.fa.fai")
    )

-   [refFlat\_hg19.txt.gz](http://www.sph.umich.edu/csg/zhanxw/software/anno/resources/refFlat_hg19.txt.gz"http://www.sph.umich.edu/csg/zhanxw/software/anno/resources/refFlat_hg19.txt.gz")
    Gene database in refFlat format (from UCSC website). You can also
    use [Gencode version
    7](http://www.sph.umich.edu/csg/zhanxw/software/anno/resources/refFlat.gencode.v7.gz "http://www.sph.umich.edu/csg/zhanxw/software/anno/resources/refFlat.gencode.v7.gz")
    or [Gencode version
    11](http://www.sph.umich.edu/csg/zhanxw/software/anno/resources/refFlat.gencode.v11.gz "http://www.sph.umich.edu/csg/zhanxw/software/anno/resources/refFlat.gencode.v11.gz").

-   [codon.txt](http://www.sph.umich.edu/csg/zhanxw/software/anno/codon.txt "http://www.sph.umich.edu/csg/zhanxw/software/anno/codon.txt")
    Human codon table.

-   [priority.txt](http://www.sph.umich.edu/csg/zhanxw/software/anno/priority.txt "http://www.sph.umich.edu/csg/zhanxw/software/anno/priority.txt")
    Priority file, which determines wich annotation type is more
    important

NOTE: a script, 'resources/download.sh,  can conveniently download all above files.


Outputs:

Annotated VCF will be named *output.vcf*. Annotations comes in two tags:
ANNO and ANNOFULL. The first tag ANNO showed the most important
annotation types (determined by priority file); the second tag ANNOFULL
showed detailed annotations. Let's see one example annotation:

    ANNO=Nonsynonymous:GENE1|GENE3;ANNOFULL=GENE1/CODING_GENE:+:Nonsynonymous(CCT/Pro/P->CAT/His/H:Base3/30:Codon1/10:Exon1/5):Normal_Splice_Site:Exon|GENE3/CODING_GENE:-:Nonsynonymous(AGG/Arg/R->ATG/Met/M:Base30/30:Codon10/10:Exon5/5):Normal_Splice_Site:Exon|GENE2/NON_CODING_GENE:+:Upstream

ANNO tag displayed the most important variant type is *Nonsynonymous*
and that happened at GENE1 and GENE3; ANNOFULL tag is the full set of
annotation and it consists of two parts, for GENE1 and GENE3
respectively. The first part is for GENE1:

    GENE1/CODING_GENE:+:Nonsynonymous(CCT/Pro/P->CAT/His/H:Base3/30:Codon1/10:Exon1/5):Normal_Splice_Site:Exon

The format can be explained by sections, and we use annotation for GENE1
as an example:

-   GENE1 : gene name
-   CODING\_GENE : transcript name
-   *+* : forward strand
-   Nonsynonymous, Normal\_Splice\_Site, Exon : various annotation types
-   CCT/Pro/P-\>CAT/His/H : Proline to Histidine mutation
-   Base3/30 : mutation happens on the 3rd base of the total 10 bases
-   Codon1/10 : mutation happens on the 1st codon of the total 10 codons
-   Exon1/5 : mutation happens on the 1st exon of the total 5 exons

Console information:

When TabAnno finished annotation successfully, you will see it output
necessary information as below. You will find basic summary of reference
genome, ts/tv ratio, total number of variants and so on.

     The following parameters are available.  Ones with "[]" are in effect:
      
     Available Options
         Required Parameters : -i [input.vcf], -o [output.vcf]
            Gene Annotations :
                               -g [resources/refFlat_hg19.txt.gz]
                               -r [resources/hs37d5.fa]
                               --inputFormat [], --checkReference, -f [], -p []
                               -c [], -u [], -d [], --se [], --si []
           Other Annotations : --genomeScore [], --bed [], --tabix []
         Auxillary Functions : --outputFormat [], --indexOutput
     Use default priority file: /usr/share/anno/priority.txt
     Use default codon file: /usr/share/anno/codon.txt
     Load reference genome resources/hs37d5.fa...
     DONE: 86 chromosomes and 3137454505 bases are loaded.
     Load codon file //usr/share/anno/codon.txt...
     DONE: codon file loaded.
     Load priority file /usr/share/anno/priority.txt...
     DONE: 25 priority annotation types loaded.
     Load gene file resources/refFlat_hg19.txt.gz...
     DONE: 39173 gene loaded.
     DONE: Generated frequency of each annotype type in [ output.vcf.anno.frq ].
     DONE: Generated frequency of each highest priority annotation type in [ output.vcf.top.anno.frq ].
     Ts/Tv ratio: 0.666667
     Ts observed: 4  times; Tv observed: 6 times.
     DONE: Generated frequency of each base change in [ output.vcf.base.frq ].
     DONE: Generated frequency of each codon change in [ output.vcf.codon.frq ].
     DONE: Generated frequency of indel length in [ output.vcf.indel.frq ].
     DONE: 59 varaints are annotated.
     DONE: Generated annotation output in [ output.vcf ].
     Annotation succeed!
      

Where to Find It
================

Anno code is hosted online
[anno](https://github.com/zhanxw/anno "https://github.com/zhanxw/anno").
You can download the source, unpack the tar file and compile (type 'make').

For CSG internal users, the compiled executable file is at:
/net/fantasia/home/zhanxw/anno/executable/anno
The source code is located at: /net/fantasia/home/zhanxw/anno.

You can type 'make release' to compile your own executable file. Type "make
test1" or "make test2" will demonstrate the command line to annotate
example VCF files.

Usage
=====

Command line
------------

After you obtain the TabAnno executable (either by compiling the source
code or by downloading the pre-compiled binary file), you will find the
executable file under executable/anno.

Here is the help page by invoking TabAnno under command line with no parameters:

     some_linux_host > executable/anno
    ..............................................         
     ...      G(ene) A(nnotation)                ...       
      ...      Xiaowei Zhan, Goncalo Abecasis     ...      
       ...      zhanxw@umich.edu                    ...    
        ...      Dec 2012                            ...   
         ...      Updated May 2016                    ...  
          ...             by michael.bekaert@stir.ac.uk ... 
           .................................................
                                                         
    Required Parameters
                           -i : Specify input VCF file
                           -o : Specify output VCF file
    Gene Annotation Parameters
                           -g : Specify gene file
                           -r : Specify reference genome position
                --inputFormat : Specify format (default: vcf). "--inputFormat plain" will 
                                use first 4 columns as chrom, pos, ref, alt
             --checkReference : Check whether reference alleles matches genome reference
                           -f : Specify gene file format (default: refFlat, other optio
                                ns: knownGene, refGene)
                           -p : Specify priority of annotations
                           -c : Specify codon file (default: codon.txt)
                           -u : Specify upstream range (default: 50)
                           -d : Specify downstream range (default: 50)
                         --se : Specify splice into extron range (default: 3)
                         --si : Specify splice into intron range (default: 8)
               --outputFormat : Specify predefined annotation words (default or epact)
    Other Annotation Tools
                --genomeScore : Specify the folder of genome score (e.g. GERP=dirGerp/,
                                SIFT=dirSift/)
                        --bed : Specify the bed file and tag (e.g. ONTARGET1=a1.bed,ONT
                                ARGET2=a2.bed)
                      --tabix : Specify the tabix file and tag (e.g. abc.txt.gz(chrom=1
                                ,pos=7,ref=3,alt=4,SIFT=7,PolyPhen=10)
    Please specify input file

Input files
-----------

anno runs on the input VCF file specified on the command-line using flag
'-i'.

Additionally, you need to specify gene file using flag '-g'. You can use
the default refFlat file (using HG19 genome build) at
http://qbrc.swmed.edu/zhanxw/software/anno/resources/refFlat_hg19.txt.gz

Parameters
----------

Some of the command line parameters are described here, but most are
self explanatory.

-   Reference genome file

<!-- -->

    -r Specify a FASTA format reference genome file.

Specifying *-r* option enable TabAnno to give more detailed information, for
example, instead of annotating a variant as exon, it will tell you which
codon, which exon that variant locates, whether its
synonymous/non-synonymous and etc.

Anno requires Fasta index file and that will save running memory and
speed up annotation. You can use "samtools faidx XXX.fa" to generate
Fasta index file.

For example, you can specify Fasta file of the whole genome and use "-r
/data/local/ref/karma.ref/human.g1k.v37.fa"

-   Gene file format

Currently, TabAnno supports gene file in refFlat format. A prepared list of
all gene obtained of UCSC website is:
"http://qbrc.swmed.edu/zhanxw/software/anno/resources/refFlat_hg19.txt.gz".
To use that file, you use flag *-g*.

As TabAnno supports refFlat file by default, you can use refFlat format
without specify gene format flag *-f*.

To use knownGene or refGene format, you need to specify both *-g* and
*-f* flat to tell TabAnno which gene file and which format it is. For
example, *-g knownGene.txt.gz -f knownGene*.

-   Codon file

Codon file can tell the relationship between triplet codons and amino
acids. A default file is located in:
*/usr/share/anno/codon.txt*. If you have special codon
file, you can specify that using flag *-c*, otherwise, TabAnno will use the
default codon file:

*default codon file*

    # DNA codon table. Stop codon is coded as: Stp, O, Stop
    #Codon      AminoAcid   Letter   FullName
    AAA     Lys     K       Lysine
    AAC     Asn     N       Asparagine
    AAG     Lys     K       Lysine
    AAT     Asn     N       Asparagine
    ACA     Thr     T       Threonine
    ...

-   Annotation ranges

<!-- -->

    -u how far apart from 5'-end of the gene are counted as upstream
    -d how far apart from 3'-end of the gene are counted as downstream

The *-u* and *-d* parameters define the range of upstream and
downstream.

    -se how far apart from 5'-end of the gene are counted as upstream
    -si how far apart from 3'-end of the gene are counted as upstream

The *-se* and *-si* defines the splice region. By default, 3 bases into
the exon and 8 bases into the introns are defined as splicing sites. If
mutations happen in these regions, we will annotate it as
"Normal\_Splice\_Site" unless the mutations happens in the traditionally
important "GU...AG" region in the intron, in that case, we will
"Essential\_Splice\_Site" as annotation.

-   Annotate by range

<!-- -->

                        --bed : Specify the bed file and tag (e.g. ONTARGET1=a1.bed,ONTARGET2=a2.bed)

BED file is commonly used to represent range. Here you will check if
certain genome position is contained in one or more ranges specified in
the BED format. An example BED file, example.bed, is as follows:

    1 10 20 a
    1 15 40 b

There are two ranges: range a is from chromsome 1 position 10
(inclusive) to chromosome 1 position 20 (exclusive); range b is from
chromsome 1 position 15 (inclusive) to chromosome 1 position 40
(exclusive).

When use *--bed ONTARGET=example.bed* as parameter, the output may look
like this: *ONTARGET=a,b* in the VCF INFO field.

-   Annotate by genome score

<!-- -->

                --genomeScore : Specify the folder of genome score (e.g. GERP=dirGerp/,SIFT=dirSift/)

Genome score is a special binary file format (designed by Hyun) storing
per-position genome score, such as GERP score, SIFT score. You will need
to pre-process those scores in a directory. To annotate genome score,
use *--genomeScore TAG\_NAME=DIRECTORY*. In VCF output file, you will
have *TAG\_NAME=some\_value* in the INFO field. In other output format,
you will see a separate column.

-   Annotate by tabix input

<!-- -->

                      --tabix : Specify the tabix file and tag (e.g. abc.txt.gz(chrom=1,pos=7,ref=3,alt=4,SIFT=7,PolyPhen=10)

Tabix file can be used in annotation. Here we required you provide
bgzipped, indexed file. In above example, we use abc.txt.gz as input,
and column 1,7,3,4 as chromosome, position, reference allele,
alternative allele. We also use column 7 as SIFT score and column 10 as
PolyPhen score. Similar syntax as previous, you will get outputs similar
to 'SIFT=0.110;PolyPhen=0.00' in the VCF INFO field. NOTE, in bash,
please use quote around parenthesis, otherwise parenthesis is not
correctly treated. A working example is as follows:

                       --tabix 'hg19_ljb_all.txt.gz(chrom=1,pos=2,ref=4,alt=5,mySift=6,mySC=7,myPP2=8,myPC=9)' 


Example
=======

anno can annotate a VCF file and also output statistics of 4 frequency
table: annotation type; base change; codon change; indel size. More
details will be given below.

Built-in example
----------------

In example/ folder, you can see test.vcf, which is a toy example. You
can invoke TabAnno using the following command line:

    cd example; ./anno -i test.vcf -r test.fa -g test.gene.txt -c ../codon.txt -o test.out.vcf

Sample outputs are listed below:

\1) Annotated VCF file, *test.out.vcf*

    #VCF_test
    #from http://www.sph.umich.edu/csg/liyanmin/vcfCodingSnps/Tutorial.shtml
    #CHROM  POS     ID      REF     ALT     QUAL    FILTER  INFO    FORMAT  NA12891 NA12892 NA12878
    1       3       .       A       G       50      depth=20        ANNO=GENE1/CODING_GENE:+:Exon:Utr5:Normal_Splice_Site|GENE3/CODING_GENE:-:Exon:Utr3:Normal_Splice_Site|GENE2/NON_CODING_GENE:+:Upstream GT:GQ:GD        1/0:31:12       0/0:28:14
    1       5       .       C       A       50      depth=20        ANNO=GENE1/CODING_GENE:+:Exon:Nonsynonymous(CCT/Pro/P->CAT/His/H:Base3/30:Codon1/10:Exon1/5):Normal_Splice_Site|GENE3/CODING_GENE:-:Exon:Nonsynonymous(AGG/Arg/R->ATG/Met/M:Base30/30:Codon10/10:Exon5/5):Normal_Splice_Site|GENE2/NON_CODING_GENE:+:Upstream   GT:GQ:GD        1/0:31:12       0/0:28:14
    ...

The annotation results are stored in the INFO column after ANN= tag. The
annotation format is defined as following:

"|" separates different transcripts, e.g. in the first line, chromosome
1 position 3, there are 3 annotations:
"GENE1/CODING\_GENE:+:Exon:Utr5:Normal\_Splice\_Site" and
"GENE3/CODING\_GENE:-:Exon:Utr3:Normal\_Splice\_Site" and
"GENE2/NON\_CODING\_GENE:+:Upstream"

":" separates within gene annotation in the following order: gene,
strand, exon/intron, details.

\2) Statistics files:

Four frequency table will be generated after annotation. For example:

*test.out.vcf.anno.frq*

    Stop_Loss       1
    Utr5    2
    Utr3    2
    CodonRegion     2
    CodonGain       2
    Frameshift      2
    Synonymous      3
    StructuralVariation     3
    Noncoding       3
    Nonsynonymous   4
    Deletion        6
    Upstream        6
    Insertion       6
    Essential_Splice_Site   8 
    Downstream      8
    Intron  12
    Exon    21
    Normal_Splice_Site      25

*test.out.vcf.base.frq*

    A->G    1
    T->C    1
    T->G    2
    A->C    2
    C->A    5

*test.out.vcf.codon.frq*

    Arg->Met        1
    Pro->Thr        1
    Arg->Arg        1
    Pro->His        1
    Gly->Gly        1
    Pro->Pro        1
    Stp->Tyr        1
    Leu->Val        1

*test.out.vcf.indel.frq*

    1       1
    -4      1
    3       1
    -3      1

Contact
=======

Questions and requests should be sent to Xiaowei Zhan
([zhanxw@umich.edu](mailto:zhanxw@umich.edu "mailto:zhanxw@umich.edu"))
or Goncalo Abecasis
([goncalo@umich.edu](mailto:goncalo@umich.edu "mailto:goncalo@umich.edu"))

Author sincerly appreicate Yanming Li for his wonderful tutorial on gene
annotation software
[vcfCodingSnps](http://www.sph.umich.edu/csg/liyanmin/vcfCodingSnps/Tutorial.shtml "http://www.sph.umich.edu/csg/liyanmin/vcfCodingSnps/Tutorial.shtml"),
and Hyun Ming Kang for his code related to genome scores and his
consistent suggestions and feedbacks.


[![Bitdeli Badge](https://d2weczhvl823v0.cloudfront.net/zhanxw/anno/trend.png)](https://bitdeli.com/free "Bitdeli Badge")

