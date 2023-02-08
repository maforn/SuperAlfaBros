//
// Created by enrico on 24/01/23.
//

#include "Weapon.hpp"

void Weapon::pointLeft() {
    if (isRight) {
        isRight = false;
        drawing = drawingLeft;
    }
}

void Weapon::pointRight() {
    if (!isRight) {
        isRight = true;
        drawing = drawingRight;
    }
}

int Weapon::getDamage() {
    return damage;
}

Weapon::Weapon(int x, int y, char objectType, std::wstring name, int damage, int range,
               std::wstring drawingLeft, std::wstring drawingRight, std::wstring drawing) : Object(x, y, drawing,
                                                                                                   objectType) {
    this->damage = damage;
    this->drawingRight = drawingRight;
    this->drawingLeft = drawingLeft;
    this->isRight = true;
    covering = L" ";
    this->name = name;
    this->range = range;

}

void Weapon::useRight(WINDOW *win) {
    if (!isRight) {
        x = x + 2;
    }
    pointRight();
}

void Weapon::useLeft(WINDOW *win) {

    if (isRight) {
        x = x - 2;
    }
    pointLeft();
}

void Weapon::moveWeapon(WINDOW *win, int x, int y) {
    this->x = x;
    this->y = y;
}

int Weapon::getRange() const {
    return this->range;
}

std::wstring Weapon::getName() {
    return this->name;
}
