//
// Created by enrico on 24/01/23.
//

#include "weapon.hpp"

void Weapon::pointLeft() {
    drawing = drawingLeft;
}

void Weapon::pointRight() {
    drawing = drawingRight;
}

int Weapon::getDamage(){
    return level*damage;
}

void Weapon::decrementLevel() {
    level--;
}

void Weapon::incrementLevel() {
    level++;
}
