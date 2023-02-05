//
// Created by vboxuser on 23.01.23.
//

#ifndef SUPERALFABROS_WEAPONLIST_HPP
#define SUPERALFABROS_WEAPONLIST_HPP


#include <string>
using namespace std;

class WeaponList{
protected:

    // struct to represent weapons and definition of pointer type
    struct weapon;
    typedef weapon* p_weapon;

    // pointer to the head of the list
    p_weapon head;

    // returns a pointer to the weapon with the specified code. Returns NULL if such weapon is not found.
    p_weapon findWeapon(char code);

    // returns a pointer to the weapon in position=index in the list. Returns NULL if such weapon is not found.
    p_weapon findWeaponByIndex(int index);

    // inserts element at the end of the list starting with head and returns the new head
    p_weapon tailInsert(p_weapon head, p_weapon element);

    // inserts element at the beginning of the list starting with head and returns the new head
    p_weapon headInsert(p_weapon head, p_weapon element);

    // skips the weapon with the specified code in the list starting with head (NO DELETION) and returns the new head
    p_weapon skipWeapon(p_weapon head, char code);

public:
    // constructor: initializes and empty list
    WeaponList();

    // adds a weapon with the specified attributes at the end of the list
    void addWeapon(char code, wstring name, int range, int damage, int startingPrice);

    // returns the number of weapons in the list
    int getCount();

    // returns the price of the weapon with the specified code. Returns -1 if such weapon is not found
    int getPrice(char code);

    // returns the damage of the weapon with the specified code. Returns -1 if such weapon is not found
    int getDamage(char code);

    // returns the code of the weapon in position=index in the list. Returns / if such weapon is not found
    char getCodeByIndex(int index);

    // sets the price of the weapon with the specified code to zero
    void removePrice(char code);

    // set the actual price of each weapon to its starting price * multiplier
    void multiplyPrices(double multiplier);

    // moves the weapon with the specified code at the beginning of the list
    void moveToFirst(char code);

    // sorts weapon by putting those with price = 0 at the beginnig of the list
    void sortWeapons();

    // generates strings containing the weapons values and inserts them into dest
    // count indicates the maximum number of strings to insert into dest
    // selectedCode indicates the code of the weapon whose string must contain the label "Selected"
    void getWeaponInfoString(wstring dest[], int count, char selectedCode);
};

#endif //SUPERALFABROS_WEAPONLIST_HPP
