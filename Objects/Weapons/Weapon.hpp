//
// Created by enrico on 24/01/23.
//

#ifndef SUPERALFABROS_WEAPON_HPP
#define SUPERALFABROS_WEAPON_HPP

#include "../Object.hpp"
#include <ncurses.h>


class Weapon : public Object{
protected:
    int level;
    int damage;
    std::wstring drawingRight;
    std::wstring drawingLeft;
public:
    Weapon(int x, int y, int level, int damage, std::wstring drawing, char objectType, std::wstring drawingRight, std::wstring drawingLeft);
    int getDamage();
    void pointRight();
    void pointLeft();
};


#endif //SUPERALFABROS_WEAPON_HPP
