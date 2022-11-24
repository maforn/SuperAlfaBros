//
// Created by matteo on 23/11/2022.
//

#ifndef SUPERALFABROS_TELEPORTER_HPP
#define SUPERALFABROS_TELEPORTER_HPP
#include "Object.hpp"

class Teleporter: public Object{
protected:
    int teleport_x;
    int teleport_y;
public:
    Teleporter(int x, int y, int teleport_x, int teleport_y);
    void teleport_to(Object &obj);
};

// set a name for the pointer to the class Teleporter
typedef Teleporter *pTeleporter;

#endif //SUPERALFABROS_TELEPORTER_HPP
