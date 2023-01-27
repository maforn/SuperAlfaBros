//
// Created by matteo on 23/11/2022.
//

#ifndef SUPERALFABROS_MAP_HPP
#define SUPERALFABROS_MAP_HPP

#include <string>
#include <fstream>
#include <iostream>
#include "../Objects/Player.hpp"
#include "../Objects/AllObjects.hpp"
#include "../Lists/DynamicObjectList.hpp"

using namespace std;

#define OBJECT_TABLE_LENGTH 30

// this class contains a map and all the objects inside
class Map {
protected:
    // name or path of the file that contains the instructions
    string fileName;
    // instance ot the dynamic object list containing various objects such as enemies, teleporters and so on
    pDynamicObjectList objectList;
    // pointer to the player instance
    pPlayer player;
    // last x position of the player to save the progress
    int lastX{};
    // last y position of the player to save the progress
    int lastY{};
    // parse object from string stored into the map file
    void objectParser(wstring line);
    // array containing line by line what will be drawn
    wstring objectTable[OBJECT_TABLE_LENGTH];
public:
    // Constructor of the class: will set the player pointer, read the file and create the dynamic object list from
    // there, as well as spawning the Player
    Map(const string& fileName, pPlayer player);

    // set the map as the first one: remove the left exit
    void setFirstMap();
    // draw the skeleton of the map that was read from the file
    void drawBaseMap(WINDOW *win, int verticalShift);
    // draw the objects contained in the object list
    void drawObjects(WINDOW *win, int verticalShift);
    // set the player coord to lastX and lastY
    void spawnPlayer();
    // save the player coord to lastX and lastY
    void savePlayerCoord();
    // detect player collision with objects
    char detectCollision(int x, int y, pObject &pObj);
    // remove and object from the objectList
    void removeObject(pObject pObj);

    // Destructor of the class: delete free pointers
    ~Map();
};

// set a name for the pointer to the class Map
typedef Map *pMap;


#endif //SUPERALFABROS_MAP_HPP
