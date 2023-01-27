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
    char direction;
public:
    Bullet(int x, int y, int level, char direction);
    virtual void move(WINDOW *win);
};


#endif //SUPERALFABROS_BULLET_HPP
