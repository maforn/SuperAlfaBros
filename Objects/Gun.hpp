//
// Created by enrico on 24/01/23.
//

#ifndef SUPERALFABROS_GUN_HPP
#define SUPERALFABROS_GUN_HPP

#include "Object.hpp"
#include "Weapon.hpp"
#include <ncurses.h>

class Gun : public Weapon{
protected:
public:
    Gun(int x, int y, int level);
};


#endif //SUPERALFABROS_GUN_HPP
