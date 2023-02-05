//
// Created by admin on 24/11/2022.
//

#ifndef SUPERALFABROS_PLAYER_HPP
#define SUPERALFABROS_PLAYER_HPP

#include "Object.hpp"
#include "Weapons/Weapon.hpp"
#include <ncurses.h>

// subclass of the superclass Object, will inherit all the characteristic of Object. Implements the player
class Player: public Object {
protected:
    // how much life the player has
    int life;
    // how much damage the player deals
    int damage{};

    pWeapon weapon;
public:
    // Constructor of the class: will set the new vars and use the constructor of the superclass
    Player(int x, int y, int life);

    // calculate damage scaled on the level TODO: use a decent equation
    int calculateDamage ();
    // draw the player on a screen
    void drawPlayer(WINDOW *win);
    // the player receives a certain amount of damage
    void receiveDamage(int dmg);
    // get the player life
    int getLife();
    // return the weapon of the player
    pWeapon  getWeapon();
    // set the weapon of the player
    void setWeapon(pWeapon newWeapon);
    void useWeaponRight(WINDOW *win);
    void useWeaponLeft(WINDOW *win);
    void movePlayer(WINDOW *win, int x, int y);

    void removeWeapon();
    pWeapon changeWeapon(pWeapon newWeapon);
};

// set a name for the pointer to the class Player
typedef Player *pPlayer;


#endif //SUPERALFABROS_PLAYER_HPP
