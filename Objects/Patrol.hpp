//
// Created by enrico on 03/01/23.
//

#ifndef SUPERALFABROS_PATROL_HPP
#define SUPERALFABROS_PATROL_HPP


#include "Object.hpp"
#include <ncurses.h>

class Patrol: public Object  {
protected:
    int x1,y1,x2,y2; // x and y of the Patrol
    bool direction; // true = x1,y1 -> x2,y2, false = x2,y2 -> x1,y1
public:
    int damage;
    int life;
    Patrol(int x, int y, int toX, int toY, int life, int damage);
    void drawPatrol(WINDOW *win);
    void move(WINDOW *win, int x, int y);
    pCords getNewPos();
    int getDamage();

};

typedef Patrol *pPatrol;

#endif //SUPERALFABROS_PATROL_HPP
