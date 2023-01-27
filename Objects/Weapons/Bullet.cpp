//
// Created by enrico on 26/01/23.
//

#include "Bullet.hpp"


Bullet::Bullet(int x, int y, int level, char direction) : Weapon(x, y, level, level+3, L"-", 'w', L"-", L"-" ){
    this->direction = direction;
}

void Bullet::move(WINDOW *win) {
    if (direction == 'r') {
        x++;
    } else if (direction == 'l') {
        x--;
    }
    this->draw(win);
}
