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
    Patrol(int x, int y, int x1, int y1, int x2, int y2);
    void drawPatrol(WINDOW *win);
    virtual void move(WINDOW *win);
};


#endif //SUPERALFABROS_PATROL_HPP
