#ifndef _STRINGUTIL_H_
#define _STRINGUTIL_H_

/** tokenize the string
    @return number of tokens we obtained
    e.g. For empty input string, we will return 1, and result will have
only 1 element (the empty string)
*/
int stringTokenize(const std::string& str, const std::string& delim, std::vector<std::string>* result){
    assert(result);
    result->clear();
    std::string s;
    unsigned int l = str.size();
    unsigned int i = 0;
    while (i < l) {
        if (delim.find(str[i]) != std::string::npos) { // it's a delimeter
            result->push_back(s);
            s.clear();
        } else {
            s.push_back(str[i]);
        }
        ++i;
    };
    result->push_back(s);    
    return result->size();
};
int stringTokenize(const std::string& str, const char delim, std::vector<std::string>* result){
    std::string d;
    d.push_back(delim);
    return (stringTokenize(str, d, result));
};

//remove leading and trailing characters
void stringStrip(std::string* input, const char* characters = " ") {
    size_t beg = input->find_first_not_of(characters);
    size_t end = input->find_last_not_of(characters);
    input->assign( input->substr(beg, end-beg) );
};

// 
void stringSlice(std::string* input, int beg, int end) {
    assert(input);
    unsigned int len = input->size();
    if (beg < 0) beg += len;
    if (end < 0) end += len;
    assert (beg >= 0 && end >= 0);
    input -> assign ( input->substr(beg, end- beg)) ;
};
#endif /* _STRINGUTIL_H_ */