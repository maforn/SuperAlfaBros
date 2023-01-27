//
// Created by enrico on 24/01/23.
//

#include "Weapon.hpp"

void Weapon::pointLeft() {
    if(isRight){
        isRight = false;
        drawing = drawingLeft;
    }
}

void Weapon::pointRight() {
    if(!isRight){
        isRight = true;
        drawing = drawingRight;
    }
}

int Weapon::getDamage(){
    return level*damage;
}

Weapon::Weapon(int x, int y, int level, int damage, std::wstring drawing, char objectType, std::wstring drawingRight, std::wstring drawingLeft) : Object(x, y, drawing, objectType) {
    this->level = level;
    this->damage = damage;
    this->drawingRight = drawingRight;
    this->drawingLeft = drawingLeft;
    this->isRight = true;
    covering = L" ";
}

void Weapon::useRight(WINDOW *win) {
    if (!isRight) {
        mvwaddwstr(win, this->y, this->x, covering);  // erase the weapon from the screen
        x=x+2;
    }
    pointRight();
    this->draw(win);
}

void Weapon::useLeft(WINDOW *win) {

    if (isRight) {
        mvwaddwstr(win, this->y, this->x, covering);  // erase the weapon from the screen
        x=x-2;
    }
    pointLeft();
    this->draw(win);
}

void Weapon::moveWeapon(WINDOW *win, int x, int y) {
    mvwaddwstr(win, this->y, this->x, covering);  // erase the weapon from the screen

    this->x = x;
    this->y = y;
    draw(win);  // draw the weapon on the new position
}

void Weapon::spown() {
    // increment

}
