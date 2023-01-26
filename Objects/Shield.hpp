//
// Created by enrico on 26/01/23.
//

#ifndef SUPERALFABROS_SHIELD_HPP
#define SUPERALFABROS_SHIELD_HPP

#include "Object.hpp"
#include "Weapon.hpp"
#include <ncurses.h>

class Shield: public Weapon{
protected:
    int life;
public:
    Shield(int x, int y, int level);
    int getLife();
    void setLife(int life);
    void receiveDamage(int damage);
};


#endif //SUPERALFABROS_SHIELD_HPP
