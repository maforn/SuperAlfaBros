//
// Created by matteo on 23/11/2022.
//

#ifndef SUPERALFABROS_TELEPORTER_H
#define SUPERALFABROS_TELEPORTER_H
#include "Object.hpp"

class Teleporter: public Object{
    protected:
        int teleport_x;
        int teleport_y;
    public:
        Teleporter(int x, int y, int teleport_x, int teleport_y);
        void teleport_to(Object &obj);











    private:
};


#endif //SUPERALFABROS_TELEPORTER_H
