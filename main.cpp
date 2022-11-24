//
// Created by matteo on 23/11/2022.
//
#include "DynamicLevelList.hpp"


int main () {
    // create a new player instance
    pPlayer player = new Player();
    string mapsFolder = "..\\maps\\";
    // create the levels dynamic lists
    pDynamicLevelList levels = new DynamicLevelList(player, mapsFolder);

    return 0;
}