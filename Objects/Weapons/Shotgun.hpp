//
// Created by enrico on 24/01/23.
//

#ifndef SUPERALFABROS_SHOTGUN_HPP
#define SUPERALFABROS_SHOTGUN_HPP

#include "../AllObjects.hpp"
#include <ncurses.h>

class Shotgun : public Weapon{
protected:
public:
    Shotgun(int x = 0, int y = 0);
};

typedef Shotgun *pKnife;
#endif //SUPERALFABROS_SHOTGUN_HPP
