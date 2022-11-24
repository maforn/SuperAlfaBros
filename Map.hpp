//
// Created by matteo on 23/11/2022.
//

#ifndef SUPERALFABROS_MAP_HPP
#define SUPERALFABROS_MAP_HPP

#include <string>
#include <fstream>
#include <iostream>
#include "Player.hpp"
#include "Teleporter.hpp"
#include "DynamicObjectList.hpp"

using namespace std;

// create a class Map that will contain a map and all the objects inside
class Map {
protected:
    // name or path of the file that contains the instructions
    string fileName;
    // array containing line by line what will be drawn
    string objectTable[30];
    // instance ot the dynamic object list containing various objects such as enemies, teleporters and so on
    pDynamicObjectList objectList{};
    // pointer to the player instance
    pPlayer player;
    // last x position of the player to save the progress
    int lastX;
    // last y position of the player to save the progress
    int lastY;
public:
    // Constructor of the class: will set the player pointer, read the file and create the dynamic object list from
    // there, as well as spawning the Player
    Map(const string& fileName, pPlayer player);

    // set the player coord to lastX and lastY
    void spawnPlayer();
    // save the player coord to lastX and lastY
    void savePlayerCoord();
};

// set a name for the pointer to the class Map
typedef Map *pMap;


#endif //SUPERALFABROS_MAP_HPP
