//
// Created by matteo on 23/11/2022.
//

#include "Map.hpp"

const char crlf = '\r\n';

Map::Map(string fileName) {
    this->fileName = fileName;
    this->objectList = new DynamicObjectList();
    this->objectList->add_head(new Teleporter(1,2,3,4));
    this->objectList->add_tail(new Teleporter(2,2,3,4));
    ifstream inputFile; /* Dichiarazione di tipo */
    inputFile.open(fileName);
    int column = 0;
    if(!inputFile.is_open()) {
        perror("Error open");
        exit(EXIT_FAILURE);
    }
    while(getline(inputFile, this->objectTable[column])) {
        column++;
    }
    inputFile.close();
}