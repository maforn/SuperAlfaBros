//
// Created by matteo on 23/11/2022.
//

#include "Teleporter.hpp"

Teleporter::Teleporter(int x, int y, int teleport_x, int teleport_y): Object(x,y, '@', 'T') {
    this->teleport_x = teleport_x;
}

void Teleporter::teleport_to(Object &obj) {
    obj.x = this->teleport_x;
    obj.y = this->teleport_y;
}