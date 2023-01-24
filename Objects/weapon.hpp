//
// Created by enrico on 24/01/23.
//

#ifndef SUPERALFABROS_WEAPON_HPP
#define SUPERALFABROS_WEAPON_HPP

#include "Object.hpp"
#include <ncurses.h>


class Weapon : public Object{
protected:
    int level;
    int damage;
    std::wstring drawingRight;
    std::wstring drawingLeft;
public:
    void incrementLevel();
    void decrementLevel();
    int getDamage();
    void pointRight();
    void pointLeft();
};


#endif //SUPERALFABROS_WEAPON_HPP
