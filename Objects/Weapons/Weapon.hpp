//
// Created by enrico on 24/01/23.
//

#ifndef SUPERALFABROS_WEAPON_HPP
#define SUPERALFABROS_WEAPON_HPP

#include "../Object.hpp"
#include <ncurses.h>


class Weapon : public Object{
protected:
    int damage;
    std::wstring drawingRight;
    std::wstring drawingLeft;
    const wchar_t *covering;
    std::wstring name;
    int range;
public:
    std::wstring getName();
    int getRange() const;
    bool isRight;
    Weapon(int x, int y, char objectType, std::wstring name, int damage, int range,
           std::wstring drawingLeft, std::wstring drawingRight, std::wstring drawing);
    int getDamage();
    virtual void useRight(WINDOW *win);
    virtual void useLeft(WINDOW *win);
    void pointRight();
    void pointLeft();
    void moveWeapon(WINDOW *win, int x, int y);
};

typedef Weapon *pWeapon;

#endif //SUPERALFABROS_WEAPON_HPP
