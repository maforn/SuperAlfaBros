//
// Created by vboxuser on 23.01.23.
//

#include "SkinList.hpp"

struct SkinList::skin{
    int price;
    char code;
    wstring drawing;
    wstring name;
    skin* next;
};


SkinList::p_skin SkinList::findSkin(char code){
    p_skin iterator = this -> head;
    while(iterator != NULL && iterator -> code != code)
        iterator = iterator -> next;
    return iterator;
}

SkinList::p_skin SkinList::findSkinByIndex(int index){
    p_skin iterator = this -> head;
    while(iterator != NULL && index > 0){
        iterator = iterator -> next;
        index -= 1;
    }
    return iterator;
}


SkinList::p_skin SkinList::tailInsert(p_skin head, p_skin element){
    if(head == NULL)
        return element;
    else{
        head -> next = tailInsert(head -> next, element);
        return head;
    }
}

SkinList::p_skin SkinList::headInsert(p_skin head, p_skin element){
    element -> next = head;
	return element;
}

SkinList::p_skin SkinList::skipSkin(p_skin head, char code) {
    if(head == NULL)
        return NULL;
    else if(head->code == code)
        return head->next;
    else{
        head->next = skipSkin(head->next, code);
        return head;
    }
}


//PUBLIC

SkinList::SkinList(){
    this -> head = NULL;
}

void SkinList::addSkin(char code, wstring drawing, wstring name, int price){
    p_skin newHead = new skin;
    newHead -> code = code;
    newHead -> drawing = drawing;
    newHead -> name = name;
    newHead -> price = price;
    newHead -> next = NULL;

    this -> head = tailInsert(this -> head, newHead);
}

int SkinList::getCount() {
    int count = 0;
    p_skin iterator = this->head;
    while(iterator != NULL){
        count += 1;
        iterator = iterator -> next;
    }
    return count;
}

char SkinList::getCodeByIndex(int index) {
    p_skin desiredSkin = findSkinByIndex(index);
    if(desiredSkin == NULL)
        return('/');
    else
        return(desiredSkin->code);
}

void SkinList::removePrice(char code){
    p_skin desiredSkin = findSkin(code);
    if(desiredSkin != NULL)
        desiredSkin -> price = 0;
}

void SkinList::sortSkins(){
    p_skin locked = NULL, unlocked = NULL;
    p_skin iterator = this -> head;

    while(iterator != NULL){
        p_skin current = iterator;
        iterator = iterator -> next;
        current -> next = NULL;

        if(current -> price == 0)
            unlocked = tailInsert(unlocked, current);
        else
            locked = tailInsert(locked, current);
    }
    this -> head = tailInsert(unlocked, locked);
}


int SkinList::getPrice(char code){
    p_skin desiredSkin = findSkin(code);
    if(desiredSkin == NULL)
        return(-1);
    else
        return(desiredSkin -> price);
}

wstring SkinList::getDrawing(char code) {
    p_skin desiredSkin = findSkin(code);
    return(desiredSkin->drawing);
}

void SkinList::moveToFirst(char code) {
    p_skin desiredSkin = findSkin(code);
    this->head = skipSkin(head, code);
    this->head = headInsert(this->head, desiredSkin);
}

void SkinList::getSkinInfoStrings(wstring dest[], int count, char selectedCode){
    int index = 0;
    p_skin iterator = this->head;
    while(iterator != NULL && index < count){
        wstring info = iterator->drawing + L"\t\t" + iterator->name + L"\t\t";

        if(iterator->price == 0){
            if(iterator->code == selectedCode)
                info += L"Selected";
            else
                info += L"Available";
        }
        else
            info += to_wstring(iterator->price);

        dest[index] = info;
        iterator = iterator->next;
        index += 1;
    }
}

/*
string SkinList::test(){
    string res = "";
    p_skin iterator = this -> head;
    while(iterator != NULL){
        res +=  " " + iterator -> name;
        iterator = iterator -> next;
    }
    return res;
}
 */
