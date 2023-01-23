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

void Object::move(WINDOW *win) {
    // do nothing
}