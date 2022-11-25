//
// Created by admin on 24/11/2022.
//

#include "DynamicLevelList.hpp"


// the struct must contain a map class (which already has inside all the objects stored)
struct DynamicLevelList::levelStruct {
    pMap map;
    levelStruct *next;
    levelStruct *prev;
};

// initialize a new map and pass it to the list by reference
void DynamicLevelList::initialize(levelList &l) {
    // create the temporary pointer to the new level that will be linked later
    levelList tmp = new levelStruct;
    // generate a new random map from the list given (with the player pointer the enemies will also be strong enough)
    tmp->map = new Map(this->mapFiles->randomMapFile(), this->player);
    // set the next and prev pointer to null
    tmp->next = nullptr;
    tmp->prev = nullptr;
    // link the temporary pointer to the pointer passed by reference
    l = tmp;
}

// add a new map to the tail of the dynamic pointer list
void DynamicLevelList::addTail() {
    // create an iterator to reach the last node of the list
    levelList iterator = this->levels, tmp;
    // reach the last node
    while (iterator->next != nullptr) {
        iterator = iterator->next;
    }
    // create a new map
    initialize(tmp);
    // append the new map
    iterator->next = tmp;
    tmp->prev = iterator;
}

// add a new map to the head of the dynamic pointer list
void DynamicLevelList::addHead() {
    // create and initialize a new map
    levelList tmp;
    initialize(tmp);
    // set the pointers in the list
    this->levels->prev = tmp;
    tmp->next = this->levels;
}

// go to the next level (and if necessary create it)
void DynamicLevelList::nextLevel() {
    // add a new level if there is none
    if (this->levels->next == nullptr) {
        this->addTail();
    }
    //save player coord
    this->levels->map->savePlayerCoord();
    // set the current level to the next level
    this->levels = this->levels->next;
    // set player coord
    this->levels->map->spawnPlayer();
}

// go to the previous level (and if necessary create it)
void DynamicLevelList::prevLevel() {
    // add a new level if there is none
    if (this->levels->prev == nullptr) {
        this->addHead();
    }
    //save player coord
    this->levels->map->savePlayerCoord();
    // set the current level to the previous level
    this->levels = this->levels->prev;
    // set player coord
    this->levels->map->spawnPlayer();
}

/*================== PUBLIC FUNCTIONS =========================*/

// Constructor of the class: will set the pointer to the player so that the new maps will have enemies of proportional strength
// will also initialize and create the first map and set it to the internal pointer;
DynamicLevelList::DynamicLevelList(pPlayer player, const string &mapsFolder) {
    // create the dynamic list of the maps contained in the specified folder
    this->mapFiles = new MapFiles(mapsFolder);
    this->player = player;
    initialize(this->levels);
}

// returns the pointer of the current map
pMap DynamicLevelList::currentMap() {
    return this->levels->map;
}

// moves to the next map and returns the pointer
pMap DynamicLevelList::nextMap() {
    this->nextLevel();
    return this->levels->map;
}

// moves to the previous map and returns the pointer
pMap DynamicLevelList::prevMap() {
    this->prevLevel();
    return this->levels->map;
}