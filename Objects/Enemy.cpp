//
// Created by enrico on 08/02/23.
//

#include "Enemy.hpp"

Enemy::Enemy(int x, int y, int life, int damage, int range, char direction) : Object(x, y, L"⇔", 'N'){
    this->x = x;
    this->y = y;
    this->life = life;
    this->damage = damage;
    this->range = range;
    this->direction = direction;
}

char Enemy::getDirection() {
    return direction;
}

int Enemy::getDamage() {
    return damage;
}

int Enemy::getRange() {
    return range;
}
