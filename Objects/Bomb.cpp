//
// Created by matteo on 11/27/22.
//

#include "Bomb.hpp"

// Constructor of the class: will set the new vars and use the constructor of the superclass
Bomb::Bomb(int x, int y, int damage): Object(x, y, L"■", 'B') {
    this->damage = damage;
}