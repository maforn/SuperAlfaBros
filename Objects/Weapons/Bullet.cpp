//
// Created by enrico on 26/01/23.
//

#include "Bullet.hpp"


Bullet::Bullet(int x, int y, int level, char direction) : Weapon(x, y, level, level+3, L"-", 'U', L"-", L"-" ){
    this->direction = direction;
}

void Bullet::move(WINDOW *win, int x, int y) {
    mvwaddwstr(win, this->y, this->x , L" ");
    this->x=x;
    this->y=y;
    mvwaddwstr(win, this->y, this->x, this->drawing.c_str());
}

pCords Bullet::getNewPos() {
    pCords cords = new Cords();
    cords->y = this->y;
    if (direction == 'r') {
        cords->x=this->x+1;
    } else if (direction == 'l') {
        cords->x=this->x-1;
    }
    return cords;
}
