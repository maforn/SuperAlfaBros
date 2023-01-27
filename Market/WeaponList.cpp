//
// Created by vboxuser on 23.01.23.
//

#include "WeaponList.hpp"

struct WeaponList::weapon{
    char code;
    wstring name;
    int range;
    int damage;
    int price;
    weapon* next;
};

WeaponList::p_weapon WeaponList::findWeapon(char code){
    p_weapon iterator = this -> head;
    while(iterator != NULL && iterator -> code != code)
        iterator = iterator -> next;
    return iterator;
}

WeaponList::p_weapon WeaponList::findWeaponByIndex(int index){
    p_weapon iterator = this -> head;
    while(iterator != NULL && index > 0){
        iterator = iterator -> next;
        index -= 1;
    }
    return iterator;
}

WeaponList::p_weapon WeaponList::tailInsert(p_weapon head, p_weapon element){
    if(head == NULL)
        return element;
    else{
        head -> next = tailInsert(head -> next, element);
        return head;
    }
}

WeaponList::p_weapon WeaponList::headInsert(p_weapon head, p_weapon element){
    element -> next = head;
	return element;
}

WeaponList::p_weapon WeaponList::skipWeapon(p_weapon head, char code){
    if(head == NULL)
        return NULL;
    else if(head->code == code)
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

void WeaponList::addWeapon(char code, wstring name, int range, int damage, int price){
    p_weapon newHead = new weapon;
    newHead->code = code;
    newHead->name = name;
    newHead->range = range;
    newHead->damage = damage;
    newHead->price = price;
    newHead->next = NULL;

    this -> head = tailInsert(this -> head, newHead);
}

int WeaponList::getCount() {
    int count = 0;
    p_weapon iterator = this->head;
    while(iterator != NULL){
        count += 1;
        iterator = iterator -> next;
    }
    return count;
}

char WeaponList::getCodeByIndex(int index) {
    p_weapon desiredWeapon = findWeaponByIndex(index);
    if(desiredWeapon == NULL)
        return('/');
    else
        return(desiredWeapon->code);
}

int WeaponList::getPrice(char code){
    p_weapon desiredWeapon = findWeapon(code);
    if(desiredWeapon == NULL)
        return(-1);
    else
        return(desiredWeapon -> price);
}

int WeaponList::getDamage(char code) {
    p_weapon desiredWeapon = findWeapon(code);
    if(desiredWeapon == NULL)
        return(-1);
    else
        return(desiredWeapon -> damage);
}

void WeaponList::removePrice(char code){
    p_weapon desiredWeapon = findWeapon(code);
    if(desiredWeapon != NULL)
        desiredWeapon -> price = 0;
}

void WeaponList::moveToFirst(char code) {
    p_weapon desiredWeapon = findWeapon(code);
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

        if(current -> price == 0)
            unlocked = tailInsert(unlocked, current);
        else
            locked = tailInsert(locked, current);
    }
    this -> head = tailInsert(unlocked, locked);
}


void WeaponList::getWeaponInfoString(wstring dest[], int count, char selectedCode) {
    int index = 0;
    p_weapon iterator = this->head;
    while(iterator != NULL && index < count){
        wstring info = iterator->name + L"\t\t" + to_wstring(iterator->range) + L"\t\t" + to_wstring(iterator->damage) + L"\t\t";

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