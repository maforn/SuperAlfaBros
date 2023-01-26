//
// Created by enrico on 26/01/23.
//

#ifndef SUPERALFABROS_BULLET_HPP
#define SUPERALFABROS_BULLET_HPP

#include "../Object.hpp"
#include "Weapon.hpp"

#include <ncurses.h>

class Bullet : public Weapon{
protected:
public:
    Bullet(int x, int y, int level);
};


#endif //SUPERALFABROS_BULLET_HPP
