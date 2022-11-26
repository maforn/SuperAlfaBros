//
// Created by admin on 24/11/2022.
//

#include "MapFiles.hpp"
#include <dirent.h>


// the struct must contain fileName and the next pointer to the node
struct MapFiles::mapFile {
    string fileName;
    mapFile *next;
};

// initialize a new map and pass it to the list by reference
void MapFiles::initialize(pMapFile &l, string fileName) {
    pMapFile tmp = new mapFile;
    // set the fileName
    tmp->fileName = fileName;
    // set the next pointer to null
    tmp->next = nullptr;
    // link the temporary pointer to the pointer passed by reference
    l = tmp;
    // increase the struct length
    this->mapFilesLength++;
}

// add a new map to the tail of the dynamic pointer list
void MapFiles::addTail(const string& fileName) {
    if (this->mapFileList == nullptr) {
        initialize(this->mapFileList, fileName);
    } else {
        // create an iterator to reach the last node of the list
        pMapFile iterator = this->mapFileList, tmp;
        // reach the last node
        while (iterator->next != nullptr) {
            iterator = iterator->next;
        }
        // create a new mapFile
        initialize(tmp, fileName);
        // append the new mapFile
        iterator->next = tmp;
    }
}

// Constructor of the class: will read the directory and create a dynamic list with the path to the .map files
MapFiles::MapFiles(const string& mapsFolder) {
    // declare a pointer to a directory
    DIR *dir;
    struct dirent *ent;
    // try to open a directory
    if ((dir = opendir (mapsFolder.c_str())) != nullptr) {
        // iterate all the files inside the directory
        while ((ent = readdir (dir)) != nullptr) {
            // if the file is a .map save it in the dynamic list
            if (strstr(ent->d_name,".map") != nullptr) {
                // save the full path with the folder path + the file name
                this->addTail(mapsFolder + ent->d_name);
            }
        }
        // close the directory
        closedir (dir);
    } else {
        // could not open directory
        perror ("");
        throw EXIT_FAILURE;
    }
}

// return a random map file path from the dynamic list created from the directory specified initially
string MapFiles::randomMapFile() {
    // random number to choose a random map
    srand(time(nullptr));
    // select a random map files from the one we have
    int fileNumber = rand() % this->mapFilesLength;
    // create an iterator to reach the nth (fileNumber) node of the list
    pMapFile iterator = this->mapFileList;
    // iterate until we reach the required file
    for (int i = 0; i < fileNumber; ++i) {
        iterator = iterator->next;
    }
    // return the file name as a string
    return iterator->fileName;
}

// Destructor of the class: delete all pointers
MapFiles::~MapFiles() {
    pMapFile tmp;
    while (this->mapFileList != nullptr) {
        tmp = this->mapFileList;
        this->mapFileList = this->mapFileList->next;
        delete tmp;
    }
}