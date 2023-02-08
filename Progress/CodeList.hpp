//
// Created by vboxuser on 23.01.23.
//

/*
 * This class implements a list of codes (chars), where the selected code is stored as the first element.
 */

#ifndef SUPERALFABROS_CODELIST_HPP
#define SUPERALFABROS_CODELIST_HPP

#include <string>
using namespace std;

class CodeList{
protected:

    // struct to hold char codes and the associated pointer type
    struct codeElement;
    typedef codeElement* p_code;

    // pointer to the head of the list
    p_code head;

    // inserts code at the beginning of the list starting with head and returns the new head
    p_code headInsert(p_code head, char code);

    // inserts code at the end of the list starting with head and returns the new head
    p_code tailInsert(p_code head, char code);

    // removes code (WITH DELETION) from the list starting with head and returns the new head
    p_code remove(p_code head, char code);

public:

    // constructor: initializes an empty list
    CodeList();

    // add new code at the end of the list
    void addCode(char code);

    // removes the specified code from the list
    void removeCode(char code);

    // moves the desired code at the beginning of the list
    void selectCode(char code);

    // returns the current code, ie the first code of the list
    char getCurrentCode();

    // returns a string composed of all the characters in the list, from first to last
    string getCodesString();
};


#endif //SUPERALFABROS_CODELIST_HPP
