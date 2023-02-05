//
// Created by enrico on 24/01/23.
//

#ifndef SUPERALFABROS_KNIFE_HPP
#define SUPERALFABROS_KNIFE_HPP

#include "../AllObjects.hpp"
#include <ncurses.h>

class Knife : public Weapon{
protected:
public:
    Knife(int x, int y, int level);
};

typedef Knife *pKnife;
#endif //SUPERALFABROS_KNIFE_HPP
