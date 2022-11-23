//
// Created by matteo on 23/11/2022.
//

#ifndef SUPERALFABROS_MAP_HPP
#define SUPERALFABROS_MAP_HPP

#include <string>
#include <fstream>
#include <iostream>
#include "Teleporter.hpp"
#include "DynamicObjectList.hpp"

using namespace std;

class Map {
protected:
    string fileName;
public:
    string objectTable[30];
    pDynamicObjectList objectList;
    Map(string fileName);
};


#endif //SUPERALFABROS_MAP_HPP
