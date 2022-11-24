//
// Created by matteo on 23/11/2022.
//

#include "Teleporter.hpp"

// Constructor of the class: will set the new vars and use the constructor of the superclass with '@' as drawing and 'T'
// as object type
Teleporter::Teleporter(int x, int y, int teleport_x, int teleport_y): Object(x,y, '@', 'T') {
    this->teleport_x = teleport_x;
    this->teleport_y = teleport_y;
}

// teleport an Object to the specified x and y
void Teleporter::teleport_to(pObject obj) {
    obj->x = this->teleport_x;
    obj->y = this->teleport_y;
}