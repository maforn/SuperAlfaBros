//
// Created by admin on 24/11/2022.
//

#ifndef SUPERALFABROS_SPIKES_HPP
#define SUPERALFABROS_SPIKES_HPP

#include "Object.hpp"

// subclass of the superclass Object, will inherit all the characteristic of Object. Implements a trap like spikes
class Spikes: public Object{
protected:
    int damage;
public:
    // Constructor of the class: will set the new vars and use the constructor of the superclass
    Spikes(int x, int y, int damage);
};

// set a name for the pointer to the class Spikes
typedef Spikes *pSpikes;

#endif //SUPERALFABROS_SPIKES_HPP
