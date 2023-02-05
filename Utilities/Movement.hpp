//
// Created by matteo on 2/5/23.
//

#ifndef SUPERALFABROS_MOVEMENT_HPP
#define SUPERALFABROS_MOVEMENT_HPP

#include "../Lists/DynamicLevelList.hpp"
#include <string.h>

#define height 30
#define width 90
#define start_x 0
#define start_y 0
#define MAX_JUMPS 3

class Movement {
protected:
    int dx;
    int maxh;
    pObject dummy;
    pPlayer player;
    bool onJump;
    int nJumps;
public:
    Movement(pPlayer player);
    void show_title();
    void show_endscreen(WINDOW *win);
    void move(pPlayer player, char choice, pDynamicLevelList levels, bool hasLanded, WINDOW* win);

    void update_dx(int ndx);
    bool is_onJump();
    void set_endJump();

    void jump(WINDOW *win, pMap Map, pDynamicLevelList levels);
};


#endif //SUPERALFABROS_MOVEMENT_HPP
