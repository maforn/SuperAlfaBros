//
// Created by enrico on 24/01/23.
//

#include "Weapon.hpp"

void Weapon::pointLeft() {
    drawing = drawingLeft;
}

void Weapon::pointRight() {
    drawing = drawingRight;
}

int Weapon::getDamage(){
    return level*damage;
}

Weapon::Weapon(int x, int y, int level, int damage, std::wstring drawing, char objectType, std::wstring drawingRight, std::wstring drawingLeft) : Object(x, y, drawing, objectType) {
    this->level = level;
    this->damage = damage;
    this->drawingRight = drawingRight;
    this->drawingLeft = drawingLeft;
}
