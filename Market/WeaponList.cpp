//
// Created by vboxuser on 23.01.23.
//

#include "WeaponList.hpp"

struct WeaponList::weaponItem{
    int startingPrice;
    int actualPrice;
    pWeapon weapon;
    weaponItem* next;
};

WeaponList::p_weaponItem WeaponList::findWeapon(char code){
    p_weaponItem iterator = this -> head;
    while(iterator != NULL && iterator->weapon->objectType != code)
        iterator = iterator -> next;
    return iterator;
}

WeaponList::p_weaponItem WeaponList::findWeaponByIndex(int index){
    p_weaponItem iterator = this -> head;
    while(iterator != NULL && index > 0){
        iterator = iterator -> next;
        index -= 1;
    }
    return iterator;
}

WeaponList::p_weaponItem WeaponList::tailInsert(p_weaponItem head, p_weaponItem element){
    if(head == NULL)
        return element;
    else{
        head -> next = tailInsert(head -> next, element);
        return head;
    }
}

WeaponList::p_weaponItem WeaponList::headInsert(p_weaponItem head, p_weaponItem element){
    element -> next = head;
	return element;
}

WeaponList::p_weaponItem WeaponList::skipWeapon(p_weaponItem head, char code){
    if(head == NULL)
        return NULL;
    else if(head->weapon->objectType == code)
        return head->next;
    else{
        head->next = skipWeapon(head->next, code);
        return head;
    }
}


//PUBLIC

WeaponList::WeaponList(){
    this -> head = NULL;
}

void WeaponList::addWeapon(pWeapon weapon,int startingPrice){
    p_weaponItem newHead = new weaponItem;
    newHead->weapon = weapon;
    newHead->startingPrice = startingPrice;
    newHead->actualPrice = startingPrice;
    newHead->next = NULL;

    this -> head = tailInsert(this -> head, newHead);
}

int WeaponList::getCount() {
    int count = 0;
    p_weaponItem iterator = this->head;
    while(iterator != NULL){
        count += 1;
        iterator = iterator -> next;
    }
    return count;
}

char WeaponList::getCodeByIndex(int index) {
    p_weaponItem desiredWeapon = findWeaponByIndex(index);
    if(desiredWeapon == NULL)
        return('/');
    else
        return(desiredWeapon->weapon->objectType);
}

pWeapon WeaponList::getWeapon(char code){
    p_weaponItem desiredWeapon = findWeapon(code);
    if(desiredWeapon != NULL)
        return desiredWeapon->weapon;
    else
        return NULL;
}

int WeaponList::getPrice(char code){
    p_weaponItem desiredWeapon = findWeapon(code);
    if(desiredWeapon == NULL)
        return(-1);
    else
        return(desiredWeapon->actualPrice);
}

void WeaponList::removePrice(char code){
    p_weaponItem desiredWeapon = findWeapon(code);
    if(desiredWeapon != NULL){
        desiredWeapon->startingPrice = 0;
        desiredWeapon->actualPrice = 0;
    }
}

void WeaponList::multiplyPrices(double multiplier){
    p_weaponItem iterator = this->head;
    while(iterator != NULL){
        iterator->actualPrice = multiplier * iterator->startingPrice;
        iterator = iterator->next;
    }
}

/*
void WeaponList::moveToFirst(char code) {
    p_weaponItem desiredWeapon = findWeapon(code);
    this->head = skipWeapon(head, code);
    this->head = headInsert(this->head, desiredWeapon);
}

void WeaponList::sortWeapons(){
    p_weapon locked = NULL, unlocked = NULL;
    p_weapon iterator = this -> head;

    while(iterator != NULL){
        p_weapon current = iterator;
        iterator = iterator -> next;
        current -> next = NULL;

        if(current->actualPrice == 0)
            unlocked = tailInsert(unlocked, current);
        else
            locked = tailInsert(locked, current);
    }
    this -> head = tailInsert(unlocked, locked);
}
*/

void WeaponList::getWeaponInfoString(wstring dest[], int count, char selectedCode) {
    int index = 0;
    p_weaponItem iterator = this->head;
    while(iterator != NULL && index < count){

        wstring info = iterator->weapon->getName() + L"\t\t";
        info += to_wstring(iterator->weapon->getRange()) + L"\t\t";
        info += to_wstring(iterator->weapon->getDamage()) + L"\t\t";

        if(iterator->actualPrice == 0){
            if(iterator->weapon->objectType == selectedCode)
                info += L"Selected";
            else
                info += L"Available";
        }
        else
            info += to_wstring(iterator->actualPrice);

        dest[index] = info;
        iterator = iterator->next;
        index += 1;
    }
}