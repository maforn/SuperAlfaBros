//
// Created by matteo on 23/11/2022.
//

#include "Object.hpp"

// Constructor of the class: will set all the variables as specified
Object::Object(int x, int y, std::wstring drawing, char objectType) {
    this->x = x;
    this->y = y;
    this->drawing = drawing;
    this->objectType = objectType;
}
void Object::draw(WINDOW *win, int verticalShift) {
    // draw the object on the screen
    mvwaddwstr(win, y + verticalShift, x, drawing.c_str());
}