//
// Created by vboxuser on 23.01.23.
//

#include "WeaponItemList.hpp"

struct WeaponItemList::weaponItem{
    int startingPrice;
    int actualPrice;
    pWeapon weapon;
    weaponItem* next;
};

WeaponItemList::p_weaponItem WeaponItemList::findWeapon(char code){
    p_weaponItem iterator = this -> head;
    while(iterator != NULL && iterator->weapon->objectType != code)
        iterator = iterator -> next;
    return iterator;
}

WeaponItemList::p_weaponItem WeaponItemList::findWeaponByIndex(int index){
    p_weaponItem iterator = this -> head;
    while(iterator != NULL && index > 0){
        iterator = iterator -> next;
        index -= 1;
    }
    return iterator;
}

WeaponItemList::p_weaponItem WeaponItemList::tailInsert(p_weaponItem head, p_weaponItem element){
    if(head == NULL)
        return element;
    else{
        head -> next = tailInsert(head -> next, element);
        return head;
    }
}

WeaponItemList::p_weaponItem WeaponItemList::headInsert(p_weaponItem head, p_weaponItem element){
    element -> next = head;
	return element;
}

WeaponItemList::p_weaponItem WeaponItemList::skipWeapon(p_weaponItem head, char code){
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

WeaponItemList::WeaponItemList(){
    this -> head = NULL;
}

void WeaponItemList::addWeapon(pWeapon weapon, int startingPrice){
    p_weaponItem newHead = new weaponItem;
    newHead->weapon = weapon;
    newHead->startingPrice = startingPrice;
    newHead->actualPrice = startingPrice;
    newHead->next = NULL;

    this -> head = tailInsert(this -> head, newHead);
}

int WeaponItemList::getCount() {
    int count = 0;
    p_weaponItem iterator = this->head;
    while(iterator != NULL){
        count += 1;
        iterator = iterator -> next;
    }
    return count;
}

char WeaponItemList::getCodeByIndex(int index) {
    p_weaponItem desiredWeapon = findWeaponByIndex(index);
    if(desiredWeapon == NULL)
        return('/');
    else
        return(desiredWeapon->weapon->objectType);
}

pWeapon WeaponItemList::getWeapon(char code){
    p_weaponItem desiredWeapon = findWeapon(code);
    if(desiredWeapon != NULL)
        return desiredWeapon->weapon;
    else
        return NULL;
}

int WeaponItemList::getPrice(char code){
    p_weaponItem desiredWeapon = findWeapon(code);
    if(desiredWeapon == NULL)
        return(-1);
    else
        return(desiredWeapon->actualPrice);
}

void WeaponItemList::removePrice(char code){
    p_weaponItem desiredWeapon = findWeapon(code);
    if(desiredWeapon != NULL){
        desiredWeapon->startingPrice = 0;
        desiredWeapon->actualPrice = 0;
    }
}

void WeaponItemList::multiplyPrices(double multiplier){
    p_weaponItem iterator = this->head;
    while(iterator != NULL){
        iterator->actualPrice = multiplier * iterator->startingPrice;
        iterator = iterator->next;
    }
}

void WeaponItemList::moveToFirst(char code) {
    p_weaponItem desiredWeapon = findWeapon(code);
    this->head = skipWeapon(head, code);
    this->head = headInsert(this->head, desiredWeapon);
}

void WeaponItemList::sortWeapons(){
    p_weaponItem locked = NULL, unlocked = NULL;
    p_weaponItem iterator = this -> head, current = NULL;

    while(iterator != NULL){
        current = iterator;
        iterator = iterator -> next;
        current -> next = NULL;

        if(current->actualPrice == 0)
            unlocked = tailInsert(unlocked, current);
        else
            locked = tailInsert(locked, current);
    }
    this -> head = tailInsert(unlocked, locked);
}

void WeaponItemList::getWeaponInfoString(wstring dest[], int count, char selectedCode) {
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