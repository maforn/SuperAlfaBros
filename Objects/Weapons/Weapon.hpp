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
    const wchar_t *covering;
public:
    bool canBeDrawn;
    bool isRight;
    Weapon(int x, int y, int level, int damage, std::wstring drawing, char objectType, std::wstring drawingRight, std::wstring drawingLeft);
    int getDamage();
    virtual void useRight(WINDOW *win);
    virtual void useLeft(WINDOW *win);
    void pointRight();
    void pointLeft();
    void moveWeapon(WINDOW *win, int x, int y);
    void spown();
};

typedef Weapon *pWeapon;

#endif //SUPERALFABROS_WEAPON_HPP
