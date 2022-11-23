//
// Created by matteo on 23/11/2022.
//

#ifndef SUPERALFABROS_MAP_H
#define SUPERALFABROS_MAP_H
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

struct objects {

    objects *next;
    objects *previous;
};

class Map {
    protected:
        string fileName;
    public:
        string objectTable[30];
        Map(string fileName);
};


#endif //SUPERALFABROS_MAP_H
