//
// Created by vboxuser on 23.01.23.
//

#include "CodeData.hpp"

struct CodeData::codeElement{
    char code;
    codeElement* next;
};

CodeData::p_code CodeData::headInsert(p_code head, char code){
    p_code newHead = new codeElement;
    newHead->code = code;
    newHead->next = head;
    return(newHead);
}

CodeData::p_code CodeData::tailInsert(p_code head, char code){
    if(head == NULL)
        return(headInsert(head, code));
    else if(head->code == code)
        return head;
    else{
        head->next = tailInsert(head->next, code);
        return(head);
    }
}

CodeData::p_code CodeData::skipCode(p_code head, char code){
    if(head == NULL)
        return NULL;
    else if(head->code == code)
        return head->next;
    else{
        head->next = skipCode(head->next, code);
        return head;
    }
}

//public

CodeData::CodeData(){
    this->head = NULL;
}

void CodeData::addCode(char code){
    this->head = tailInsert(this -> head, code);
}

void CodeData::selectCode(char code){
    this->head = skipCode(this -> head, code);
    this->head = headInsert(this -> head, code);
}

char CodeData::getCurrentCode(){
    if(head != NULL)
        return(this->head->code);
    else
        return('/');
}

string CodeData::getCodesString(){
    string str = "";
    p_code iterator = head;
    while(iterator != NULL){
        str += (iterator->code);
        iterator = iterator->next;
    }
    return(str);
}
