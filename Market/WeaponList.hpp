//
// Created by vboxuser on 23.01.23.
//

#ifndef SUPERALFABROS_WEAPONLIST_HPP
#define SUPERALFABROS_WEAPONLIST_HPP


#include <string>
#include "../Objects/Weapons/AllWeapons.hpp"
using namespace std;

class WeaponList{
protected:

    // struct to represent weapons and definition of pointer type
    struct weaponItem;
    typedef weaponItem* p_weaponItem;

    // pointer to the head of the list
    p_weaponItem head;

    // returns a pointer to the weapon with the specified code. Returns NULL if such weapon is not found.
    p_weaponItem findWeapon(char code);

    // returns a pointer to the weapon in position=index in the list. Returns NULL if such weapon is not found.
    p_weaponItem findWeaponByIndex(int index);

    // inserts element at the end of the list starting with head and returns the new head
    p_weaponItem tailInsert(p_weaponItem head, p_weaponItem element);

    // inserts element at the beginning of the list starting with head and returns the new head
    p_weaponItem headInsert(p_weaponItem head, p_weaponItem element);

    // skips the weapon with the specified code in the list starting with head (NO DELETION) and returns the new head
    p_weaponItem skipWeapon(p_weaponItem head, char code);

public:
    // constructor: initializes and empty list
    WeaponList();

    // adds a weapon with the specified attributes at the end of the list
    void addWeapon(pWeapon weapon, int startingPrice);

    // returns the number of weapons in the list
    int getCount();

    // returns the price of the weapon with the specified code. Returns -1 if such weapon is not found
    int getPrice(char code);

    // returns the code of the weapon in position=index in the list. Returns / if such weapon is not found
    char getCodeByIndex(int index);

    pWeapon getWeapon(char code);

    // sets the price of the weapon with the specified code to zero
    void removePrice(char code);

    // set the actual price of each weapon to its starting price * multiplier
    void multiplyPrices(double multiplier);

    /*
    // moves the weapon with the specified code at the beginning of the list
    void moveToFirst(char code);

    // sorts weapon by putting those with price = 0 at the beginnig of the list
    void sortWeapons();
     */

    // generates strings containing the weapons values and inserts them into dest
    // count indicates the maximum number of strings to insert into dest
    // selectedCode indicates the code of the weapon whose string must contain the label "Selected"
    void getWeaponInfoString(wstring dest[], int count, char selectedCode);
};

#endif //SUPERALFABROS_WEAPONLIST_HPP
