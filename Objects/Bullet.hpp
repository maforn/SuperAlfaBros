//
// Created by enrico on 26/01/23.
//

#ifndef SUPERALFABROS_BULLET_HPP
#define SUPERALFABROS_BULLET_HPP

#include "Object.hpp"

#include <ncurses.h>

class Bullet : public Object{
protected:
    char direction;
    int damage;

public:
    int range;
    Bullet(int x, int y, int damage, char direction, int range, bool fromPlayer);
    void move(WINDOW *win, int x, int y);
    pCords getNewPos();
    int getDamage();
};

typedef Bullet *pBullet;
#endif //SUPERALFABROS_BULLET_HPP
