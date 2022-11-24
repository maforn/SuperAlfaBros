//
// Created by matteo on 23/11/2022.
//

#include "Map.hpp"


// Constructor of the class: will set the player pointer, read the file and create the dynamic object list from
// there, as well as spawning the Player
Map::Map(const string& fileName, pPlayer player) {
    // store the filename
    this->fileName = fileName;
    // store the pointer to the player
    this->player = player;
    // create an object list for the map
    this->objectList = new DynamicObjectList();

    // declare and then use the inputFile to open the file whose name was provided
    ifstream inputFile;
    inputFile.open(fileName);
    // check that the file can be opened
    if(!inputFile.is_open()) {
        perror("Error open");
        exit(EXIT_FAILURE);
    }

    // the first line contains all the information about where the player should spawn and which object the map
    // contains, as well as their coordinates and characteristic stored as type,x,y,...;type1,x,y,...
    string line, tmp_line;
    // get the first line
    getline(inputFile, line);
    // position of the next separator
    size_t pos = 0;
    // while separators are found, keep creating objects
    while ((pos = line.find(';')) != string::npos) {
        // get the line before the separator
        tmp_line = line.substr(0, pos);
        // DEBUG
        cout << tmp_line << endl;

        // remove, for the next iteration, the string before the separator
        line.erase(0, pos + 1);
        // get the first char of the string structured as type,x,y,...
        switch (tmp_line[0]) {
            case 'P': // case Player
                // remove the first two useless chars
                tmp_line.erase(0, 2); // remove the first two useless chars
                // set lastX to the first number before ','
                this->lastX  = stoi(tmp_line.substr(0, tmp_line.find(',')));
                // remove the x,
                tmp_line.erase(0, tmp_line.find(',') + 1);
                // set lastY to the remaining number
                this->lastY  = stoi(tmp_line);
                break;
            case 'T': // case Teleporter
                // remove the first two useless chars
                tmp_line.erase(0, 2); // remove the first two useless chars
                // create params that will be passed to the teleporter constructor
                int x, y, toX, toY;

                // set x to the first number before ','
                x = stoi(tmp_line.substr(0, tmp_line.find(',')));
                // remove the x,
                tmp_line.erase(0, tmp_line.find(',') + 1);
                // set y to the new first number before ','
                y = stoi(tmp_line.substr(0, tmp_line.find(',')));
                // remove the y,
                tmp_line.erase(0, tmp_line.find(',') + 1);
                // set toX to the new first number before ','
                toX = stoi(tmp_line.substr(0, tmp_line.find(',')));
                // remove the toX,
                tmp_line.erase(0, tmp_line.find(',') + 1);
                // set toY to the remaining number
                toY = stoi(tmp_line.substr(0, tmp_line.find(',')));

                // add to the dynamic object list the new object as an object of type Teleporter
                this->objectList->addTail(new Teleporter(x, y,toX, toY), 'T');
                break;
        }
    }


    // read the file line by line and store the graphic contained from line 2
    int column = 0;
    while(getline(inputFile, this->objectTable[column])) {
        column++;
    }
    // close the inputFile
    inputFile.close();
    // spawn the player based on the coord indicated in the file
    this->spawnPlayer();
}

// set the player coord to lastX and lastY
void Map::spawnPlayer() {
    this->player->x = this->lastX;
    this->player->y = this->lastY;
}

// save the player coord to lastX and lastY
void Map::savePlayerCoord() {
    this->lastX = this->player->x;
    this->lastY = this->player->y;
}