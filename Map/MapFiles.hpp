//
// Created by matteo on 24/11/2022.
//

#ifndef SUPERALFABROS_MAPFILES_HPP
#define SUPERALFABROS_MAPFILES_HPP

#include <string>
#include <cstring>

using namespace std;

// create a class MapFiles that will contain dynamic list of the map files path and the relative functions for manipulation
class MapFiles {
protected:
    // create a struct for the dynamic list of map file names
    struct mapFile;
    // define the pointer to the struct
    typedef mapFile *pMapFile;
    // create a pointer to the list of map file names
    pMapFile mapFileList{};
    // set an int to keep track of the length of the map file names list
    int mapFilesLength{};

    // initialize a new mapFile and pass it to the list by reference
    void initialize(pMapFile &l, string fileName);
    // add a new mapFile to the tail of the dynamic pointer list
    void addTail(const string& fileName);
public:
    // Constructor of the class: will read the directory and create a dynamic list with the path to the .map files
    MapFiles(const string& mapsFolder);

    // return a random map file path from the dynamic list created from the directory specified initially
    string randomMapFile ();

    // Destructor of the class: delete free pointers
    ~MapFiles();
};

// set a name for the pointer to the class MapFiles
typedef MapFiles *pMapFiles;

#endif //SUPERALFABROS_MAPFILES_HPP
