//
// Created by vboxuser on 23.01.23.
//


#include "RefillList.hpp"

struct RefillList::refill{
    char code;
    wstring name;
    int amount;
    int price;
    refill* next;
};

RefillList::p_refill RefillList::findRefill(char code){
    p_refill iterator = this -> head;
    while(iterator != NULL && iterator -> code != code)
        iterator = iterator -> next;
    return iterator;
}

RefillList::p_refill RefillList::findRefillByIndex(int index){
    p_refill iterator = this -> head;
    while(iterator != NULL && index > 0){
        iterator = iterator -> next;
        index -= 1;
    }
    return iterator;
}

RefillList::p_refill RefillList::tailInsert(p_refill head, p_refill element){
    if(head == NULL)
        return element;
    else{
        head -> next = tailInsert(head -> next, element);
        return head;
    }
}

//PUBLIC

RefillList::RefillList(){
    this -> head = NULL;
}

void RefillList::addRefill(char code, wstring name, int amount, int price){
    p_refill newRefill = new refill;
    newRefill -> price = price;
    newRefill -> amount = amount;
    newRefill -> code = code;
    newRefill -> name = name;
    newRefill -> next = NULL;

    this -> head = tailInsert(this -> head, newRefill);
}

int RefillList::getCount() {
    int count = 0;
    p_refill iterator = this -> head;
    while(iterator != NULL){
        count += 1;
        iterator = iterator -> next;
    }
    return count;
}

char RefillList::getCodeByIndex(int index) {
    p_refill desiredRefill = findRefillByIndex(index);
    if(desiredRefill == NULL)
        return('/');
    else
        return(desiredRefill->code);
}

int RefillList::getPrice(char code){
    p_refill desiredRefill = findRefill(code);
    if(desiredRefill == NULL)
        return(-1);
    else
        return(desiredRefill -> price);
}

int RefillList::getAmount(char code){
    p_refill desiredRefill = findRefill(code);
    if(desiredRefill == NULL)
        return(-1);
    else
        return(desiredRefill -> amount);
}

void RefillList::getRefillInfoStrings(wstring dest[], int count) {
    int index = 0;
    p_refill iterator = this->head;
    while(iterator != NULL && index < count){
        dest[index] = iterator->name + L"\t\t" + to_wstring(iterator->amount) + L"\t\t" + to_wstring(iterator->price);
        iterator = iterator->next;
        index += 1;
    }
}