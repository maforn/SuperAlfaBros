//
// Created by enrico on 26/01/23.
//

#include "Bullet.hpp"


Bullet::Bullet(int x, int y, int damage, char direction, int range, bool fromPlayer) : Object(x, y,
                                                                                              fromPlayer ? L"-" : L"*",
                                                                                              fromPlayer ? 'U' : 'V') {
    this->direction = direction;
    this->damage = damage;
    this->range = range;
}

void Bullet::move(int x, int y) {
    this->x = x;
    this->y = y;
}

pCords Bullet::getNewPos() {
    pCords cords = new Cords();
    cords->y = this->y;
    if (direction == 'r') {
        cords->x = this->x + 1;
    } else if (direction == 'l') {
        cords->x = this->x - 1;
    }
    return cords;
}

int Bullet::getDamage() {
    return this->damage;
}
