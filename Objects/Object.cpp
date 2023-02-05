//
// Created by matteo on 23/11/2022.
//

#include "Object.hpp"
#include "Patrol.hpp"

// Constructor of the class: will set all the variables as specified
Object::Object(int x, int y, std::wstring drawing, char objectType) {
    this->x = x;
    this->y = y;
    this->drawing = drawing;
    this->objectType = objectType;
}
void Object::draw(WINDOW *win) {
    // draw the object on the screen
    mvwaddwstr(win, y, x, drawing.c_str());
}

/*
void Object::move(WINDOW *win, int x, int y) {
    // do nothing
}

void Object::getNewPos(int &x, int &y) {

}
*/