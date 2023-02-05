//
// Created by admin on 24/11/2022.
//

#ifndef SUPERALFABROS_DYNAMICLEVELLIST_HPP
#define SUPERALFABROS_DYNAMICLEVELLIST_HPP

#include "../Map/Map.hpp"
#include "../Map/MapFiles.hpp"
#include <ctime>
#include <cstdlib>

// create a class for the dynamic level list that will manage all the maps and levels
class DynamicLevelList {
private:
    // create a struct for the dynamic list of maps
    struct levelStruct;
    // define the pointer to the struct
    typedef levelStruct *levelList;
    // create a pointer to the list of maps
    levelList levels{};
    // save the pointer to the player class instance
    pPlayer player;
    // pointer to the class containing all the locations of the map files
    pMapFiles mapFiles;

    // initialize a new map and pass it to the list by reference
    void initialize(levelList &l);
    // add a new map to the tail of the dynamic pointer list
    void addTail();
    // add a new map to the head of the dynamic pointer list
    void addHead();
    // go to the next level (and if necessary create it)
    void nextLevel();
    // go to the previous level (and if necessary create it)
    void prevLevel();
public:
    // Constructor of the class: will set the pointer to the player so that the new maps will have enemies of proportional strength
    // will also initialize and create the first map and set it to the internal pointer;
    DynamicLevelList(pPlayer player, const string& mapsFolder);

    // returns the pointer of the current map
    pMap currentMap();

    // move player to x y checking collisions
    void movePlayer(WINDOW* win, int x, int y);

    bool detectCollisionWeapon(int x, int y);

    // Destructor of the class: delete free pointers
    ~DynamicLevelList();
};

// set a name for the pointer to the class DynamicLevelList
typedef DynamicLevelList *pDynamicLevelList;

#endif //SUPERALFABROS_DYNAMICLEVELLIST_HPP
