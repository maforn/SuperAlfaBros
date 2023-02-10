//
// Created by matteo on 11/27/22.
//

#ifndef SUPERALFABROS_BOMB_H
#define SUPERALFABROS_BOMB_H

#include "Object.hpp"

// subclass of the superclass Object, will inherit all the characteristic of Object. Implements a one-time bomb
class Bomb: public Object{
protected:
public:
    int life;
    // Constructor of the class: will set the new vars and use the constructor of the superclass
    Bomb(int x, int y, int life, int damage, int value);

    // the damage that this will deal
    int damage;

    //value of the object in terms of points and money
    int value;
};

// set a name for the pointer to the class Spikes
typedef Bomb *pBomb;


#endif //SUPERALFABROS_BOMB_H
