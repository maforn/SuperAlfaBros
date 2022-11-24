//
// Created by admin on 24/11/2022.
//

#include "Spikes.hpp"

// Constructor of the class: will set the new vars and use the constructor of the superclass
Spikes::Spikes(int x, int y, int damage): Object(x, y, '*', 'S') {
    this->damage = damage;
}