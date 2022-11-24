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

    // all the lines starting with a letter will contain the information about where the player should spawn or about
    // which object the map contains, as well as their coordinates and characteristic stored as type,x,y,...
    string line;
    getline(inputFile, line);
    while (line[0] >= 'A' && line[0] <= 'Z') {
        // parse the object encoded into the file
        this->objectParser(line);
        getline(inputFile, line);
    }

    // set the last line that was read inside the graphic
    this->objectTable[0] = line;
    // read the remaining file line by line and store the graphic contained
    int column = 1;
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

// parse object from string stored into the map file
void Map::objectParser(string line) {
    // DEBUG
    cout << line << endl;
    // get the first char of the string structured as type,x,y,...
    switch (line[0]) {
        case 'P': // case Player
            // remove the first two useless chars
            line.erase(0, 2); // remove the first two useless chars ("P,")
            // set lastX to the first number before ','
            this->lastX  = stoi(line.substr(0, line.find(',')));
            // remove the x,
            line.erase(0, line.find(',') + 1);
            // set lastY to the remaining number
            this->lastY  = stoi(line);
            break;

        case 'T': // case Teleporter
            // remove the first two useless chars
            line.erase(0, 2); // remove the first two useless chars ("T,")
            // create params that will be passed to the teleporter constructor
            int x, y, toX, toY;

            // set x to the first number before ','
            x = stoi(line.substr(0, line.find(',')));
            // remove the x,
            line.erase(0, line.find(',') + 1);
            // set y to the new first number before ','
            y = stoi(line.substr(0, line.find(',')));
            // remove the y,
            line.erase(0, line.find(',') + 1);
            // set toX to the new first number before ','
            toX = stoi(line.substr(0, line.find(',')));
            // remove the toX,
            line.erase(0, line.find(',') + 1);
            // set toY to the remaining number
            toY = stoi(line.substr(0, line.find(',')));

            // add to the dynamic object list the new object as an object of type Teleporter
            this->objectList->addTail(new Teleporter(x, y,toX, toY));
            break;

        case 'S': // stands for spikes
            // remove the first two useless chars
            line.erase(0, 2); // remove the first two useless chars ("S,")

            // set x to the first number before ','
            x = stoi(line.substr(0, line.find(',')));
            // remove the x,
            line.erase(0, line.find(',') + 1);
            // set y to the remaining number
            y = stoi(line.substr(0, line.find(',')));

            this->objectList->addTail(new Spikes(x, y, this->player->calculateDamage()));

            break;

        default: // none of the previous cases were matched
            cout << "Invalid encoding: " << line << endl;
    }
}