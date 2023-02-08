//
// Created by vboxuser on 23.01.23.
//

#include "CodeList.hpp"

struct CodeList::codeElement{
    char code;
    codeElement* next;
};

CodeList::p_code CodeList::headInsert(p_code head, char code){
    p_code newHead = new codeElement;
    newHead->code = code;
    newHead->next = head;
    return(newHead);
}

CodeList::p_code CodeList::tailInsert(p_code head, char code){
    if(head == NULL)
        return(headInsert(head, code));
    else if(head->code == code)
        return head;
    else{
        head->next = tailInsert(head->next, code);
        return(head);
    }
}

CodeList::p_code CodeList::remove(p_code head, char code) {
    if(head == NULL)
        return NULL;
    else if(head->code == code){
        p_code tmp = head->next;
        delete(head);
        return tmp;
    }
    else{
        head->next = remove(head->next, code);
        return head;
    }
}

//PUBLIC

CodeList::CodeList(){
    this->head = NULL;
}

void CodeList::addCode(char code){
    this->head = tailInsert(this -> head, code);
}

void CodeList::removeCode(char code) {
    this->head = remove(this->head, code);
}

void CodeList::selectCode(char code){
    removeCode(code);
    this->head = headInsert(this -> head, code);
}

char CodeList::getCurrentCode(){
    if(head != NULL)
        return(this->head->code);
    else
        return('/');
}

string CodeList::getCodesString(){
    string str = "";
    p_code iterator = head;
    while(iterator != NULL){
        str += (iterator->code);
        iterator = iterator->next;
    }
    return(str);
}
