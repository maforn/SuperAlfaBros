//
// Created by admin on 24/11/2022.
//

#ifndef SUPERALFABROS_PLAYER_HPP
#define SUPERALFABROS_PLAYER_HPP

#include "Object.hpp"
#include <ncurses.h>

#define MAX_LIFE 100 // max value for player life
#define MAX_ARMOUR 50 // max value for player armour

// subclass of the superclass Object, will inherit all the characteristic of Object. Implements the player
class Player: public Object {
protected:
    // how much life the player has
    int life;
    // reduces the damage inflicted to the player
    int armour;
    // how much damage the player deals
    int damage{};
    // how far the player can hit targets from
    int range;

    // increments field by incr without exceeding maxVal. Returns false if field was already equal to maxVal
    bool incrementField(int& field, int incr, const int maxVal);

public:
    // Constructor of the class: will set the new vars and use the constructor of the superclass
    Player(int x, int y, int life);

    // calculate damage scaled on the level TODO: use a decent equation
    int calculateDamage ();
    // draw the player on a screen
    void drawPlayer(WINDOW *win, int verticalShift);
    // the player receives a certain amount of damage
    void receiveDamage(int dmg);

    // get the player life
    int getLife();
    // get the player armour
    int getArmour();
    // get the player damage
    int getDamage();

    // increments player life without exceeding max value. Returns false if player life was already equal to max.
    bool incrementLife(int incr);
    // increments player armour without exceeding max value. Returns false if player armour was already equal to max.
    bool incrementArmour(int incr);
    // changes the player damage to newVal
    void changeDamage(int newVal);
    // changes the player drawing to newSkin
    void changeSkin(std::wstring newSkin);

};

// set a name for the pointer to the class Player
typedef Player *pPlayer;


#endif //SUPERALFABROS_PLAYER_HPP
