#include "Movement.hpp"

Movement::Movement(pPlayer player) {
    this->dx = 0;
    this->maxh = height;
    this->player = player;
    this->onJump = false;
    this->nJumps = 0;
}

void Movement::update_dx(int ndx) {
    this->dx = ndx;
}

bool Movement::is_onJump() {
    return this->onJump;
}

void Movement::set_endJump() {
    this->onJump = false;
}

void Movement::jump(WINDOW *win, pMap Map, pDynamicLevelList levels) {
    if (Map->detectCollision(player->x, player->y - 1, dummy) != 'W') {
        if (Map->detectCollision(player->x, player->y + 1, dummy) != ' ' && !this->onJump) {
            this->onJump = true;
            this->maxh = player->y - 4;
            levels->movePlayer(win,player->x + dx, player->y - 1);
            levels->movePlayer(win, player->x + dx, player->y - 1);
        } else if (player->y > maxh && this->nJumps < MAX_JUMPS) {
            levels->movePlayer(win, player->x + dx, player->y - 1);
            nJumps++;

        } else {
            maxh = height;
            this->onJump = false;
        }
        levels->movePlayer(win, player->x + dx, player->y);
    } else {
        maxh = height;
        this->onJump = false;
    }
}