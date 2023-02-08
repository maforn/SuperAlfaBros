//
// Created by enrico on 24/01/23.
//

#ifndef SUPERALFABROS_GUN_HPP
#define SUPERALFABROS_GUN_HPP

#include "../Object.hpp"
#include "Weapon.hpp"
#include <ncurses.h>

class Gun : public Weapon{
protected:
public:
    Gun(int x = 0, int y = 0);
};


#endif //SUPERALFABROS_GUN_HPP
