//
// Created by matteo on 23/11/2022.
//

#ifndef SUPERALFABROS_TELEPORTER_HPP
#define SUPERALFABROS_TELEPORTER_HPP
#include "Object.hpp"

// subclass of the superclass Object, will inherit all the characteristic of Object. Implements a teleporter
class Teleporter: public Object{
protected:
    // x of the other end of the teleporter
    int teleport_x;
    // y of the other end of the teleporter
    int teleport_y;
public:
    // Constructor of the class: will set the new vars and use the constructor of the superclass
    Teleporter(int x, int y, int teleport_x, int teleport_y);

    // teleport an Object to the specified x and y
    void teleportObject(pObject obj);
};

// set a name for the pointer to the class Teleporter
typedef Teleporter *pTeleporter;

#endif //SUPERALFABROS_TELEPORTER_HPP
