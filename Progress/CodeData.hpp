//
// Created by vboxuser on 23.01.23.
//

#ifndef SUPERALFABROS_CODEDATA_HPP
#define SUPERALFABROS_CODEDATA_HPP

#include <string>
using namespace std;

class CodeData{
protected:

    // struct to hold char codes and the associated pointer type
    struct codeElement;
    typedef codeElement* p_code;

    // pointer to the head of the list
    p_code head;

    // insert code at the beginning of the list starting with head and returns the new head
    p_code headInsert(p_code head, char code);

    // insert code at the end of the list starting with head and returns the new head
    p_code tailInsert(p_code head, char code);

    // skip code in the list starting with head (NO DELETION) and returns the new head
    p_code skipCode(p_code head, char code);

public:

    // constructor: initializes an empty list
    CodeData();

    // add new code at the end of the list
    void addCode(char code);

    // moves the desired code at the beginning of the list
    void selectCode(char code);

    // returns the current code, ie the first code of the list
    char getCurrentCode();

    // returns a string composed of all the characters in the list, from first to last
    string getCodesString();
};


#endif //SUPERALFABROS_CODEDATA_HPP
