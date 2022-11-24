//
// Created by matteo on 23/11/2022.
//

#include "Object.hpp"

Object::Object(int x, int y, char drawing, char objectType) {
    this->x = x;
    this->y = y;
    this->drawing = drawing;
    this->objectType = objectType;
}