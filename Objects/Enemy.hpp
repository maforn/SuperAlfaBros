//
// Created by enrico on 08/02/23.
//

#ifndef SUPERALFABROS_ENEMY_HPP
#define SUPERALFABROS_ENEMY_HPP


#include "Object.hpp"

class Enemy : public Object {
protected:
    int damage;
    int range;
    char direction;
public:
    int life;
    int value;
    Enemy(int x, int y, int life, int damage, int range, char direction, int value);
    char getDirection();
    int getDamage();
    int getRange();
};

typedef Enemy *pEnemy;

#endif //SUPERALFABROS_ENEMY_HPP
