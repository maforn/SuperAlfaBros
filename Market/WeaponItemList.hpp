//
// Created by vboxuser on 23.01.23.
//

/*
 * This class implements a list of weaponItems for the market.
 * These weaponItems are aligned to the game Weapons: each weaponItem has pointer to an instance
 * of the corresponding Weapon.
 *
 * Since each Weapon object has a code, each weaponItem is also associated to a code, through which the item can be found
 * and accessed in the list. Given an index i, it's also possible to retrieve the code
 * associated to the item in position i in the list (if existing).
 *
 * Each weaponItem has a startingPrice, which is set when the item is created, and an actualPrice, which can be calculated
 * from the startingPrice using multiplyPrices().
 */

#ifndef SUPERALFABROS_WEAPONITEMLIST_HPP
#define SUPERALFABROS_WEAPONITEMLIST_HPP

#include <string>
#include "../Objects/Weapons/AllWeapons.hpp"
using namespace std;

class WeaponItemList{
protected:

    // struct to represent weapon items and definition of pointer type
    struct weaponItem;
    typedef weaponItem* p_weaponItem;

    // pointer to the head of the list
    p_weaponItem head;

    // returns a pointer to the weaponItem with the specified code. Returns NULL if such element is not found.
    p_weaponItem findWeapon(char code);

    // returns a pointer to the weaponItem in position=index in the list. Returns NULL if such element is not found.
    p_weaponItem findWeaponByIndex(int index);

    // inserts element at the end of the list starting with head and returns the new head
    p_weaponItem tailInsert(p_weaponItem head, p_weaponItem element);

    // inserts element at the beginning of the list starting with head and returns the new head
    p_weaponItem headInsert(p_weaponItem head, p_weaponItem element);

    // skips the weaponItem with the specified code in the list starting with head (NO DELETION) and returns the new head
    p_weaponItem skipWeapon(p_weaponItem head, char code);

public:
    // constructor: initializes and empty list
    WeaponItemList();

    // adds a weaponItem with the specified attributes at the end of the list
    void addWeapon(pWeapon weapon, int startingPrice);

    // returns the number of weaponItems in the list
    int getCount();

    // returns the price of the weaponItem with the specified code. Returns -1 if such item is not found
    int getPrice(char code);

    // returns the code of the weaponItem in position=index in the list. Returns / if such item is not found
    char getCodeByIndex(int index);

    // returns the pointer to the weapon associated to the weaponItem with the specified code
    pWeapon getWeapon(char code);

    // sets the price of the weaponItem with the specified code to zero
    void removePrice(char code);

    // set the actual price of each weaponItem to its starting price * multiplier
    void multiplyPrices(double multiplier);

    // moves the weaponItem with the specified code at the beginning of the list
    void moveToFirst(char code);

    // sorts weaponItems by putting those with price = 0 at the beginnig of the list
    void sortWeapons();

    // generates strings containing the weaponItems values (name, range, damage, price) and inserts them into dest
    // count indicates the maximum number of strings to insert into dest
    // weaponItems whose price has been set to zero will be marked as "Available"
    // selectedCode indicates the code of the available weaponItem that will be marked as "Selected"
    void getWeaponInfoString(wstring dest[], int count, char selectedCode);
};

#endif //SUPERALFABROS_WEAPONITEMLIST_HPP
