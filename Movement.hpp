//
// Created by vboxuser on 04/02/23.
//

#ifndef SUPERALFABROS_MOVEMENT_HPP
#define SUPERALFABROS_MOVEMENT_HPP
#include "Lists/DynamicLevelList.hpp"
#define height 30
#define width 90
#define start_x 0
#define start_y 0
#define MAX_JUMPS 6
void show_title();
void show_endscreen(WINDOW *win);
void move(pPlayer player, char choice, pDynamicLevelList levels, bool hasLanded);
#endif //SUPERALFABROS_MOVEMENT_HPP
