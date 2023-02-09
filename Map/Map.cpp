//
// Created by matteo on 23/11/2022.
//

#include "Map.hpp"

#include <codecvt>
#include <thread>

// Constructor of the class: will set the player pointer, read the file and create the dynamic object list from
// there, as well as spawning the Player
Map::Map(const string &fileName, pPlayer player, pProgressManager progressManager) {
    this->progressManager = progressManager;
    // store the filename
    this->fileName = fileName;
    // store the pointer to the player
    this->player = player;
    // create an object list for the map
    this->objectList = new DynamicObjectList();

    // declare and then use the inputFile to open the file whose name was provided
    wifstream inputFile;
    inputFile.open(fileName);
    // check that the file can be opened
    if (!inputFile.is_open()) {
        perror("Error open");
        exit(EXIT_FAILURE);
    }
    // all the lines starting with a letter will contain the information about where the player should spawn or about
    // which object the map contains, as well as their coordinates and characteristic stored as type,x,y,...
    wstring line;
    inputFile.imbue(locale(locale(), new codecvt_utf8<wchar_t>));
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
    while (getline(inputFile, this->objectTable[column])) {
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
    if (this->player->getWeapon() != nullptr) {
        this->player->getWeapon()->x = this->lastX + 1;
        this->player->getWeapon()->y = this->lastY;
    }

}

// save the player coord to lastX and lastY
void Map::savePlayerCoord() {
    this->lastX = this->player->x;
    this->lastY = this->player->y;
}

// parse object from string stored into the map file
void Map::objectParser(wstring line) {
    // DEBUG
    //wcout << line << endl;

    // difficulty to apply to parsed object
    double difficulty = progressManager->getDifficulty();
    int d, x1, y1, x2, y2;
    // get the first char of the string structured as type,x,y,...
    switch (line[0]) {
        case 'P': // case Player
            // remove the first two useless chars
            line.erase(0, 2); // remove the first two useless chars ("P,")
            // set lastX to the first number before ','
            this->lastX = stoi(line.substr(0, line.find(',')));
            // remove the x,
            line.erase(0, line.find(',') + 1);
            // set lastY to the remaining number
            this->lastY = stoi(line);
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
            this->objectList->addTail(new Teleporter(x, y, toX, toY));
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

        case 'B': // stands for bomb
            // remove the first two useless chars
            line.erase(0, 2); // remove the first two useless chars ("B,")

            // set x to the first number before ','
            x = stoi(line.substr(0, line.find(',')));
            // remove the x,
            line.erase(0, line.find(',') + 1);
            // set y to the remaining number
            y = stoi(line.substr(0, line.find(',')));

            this->objectList->addTail(new Bomb(x, y, 50 * difficulty, 20 * difficulty));

            break;

        case 'R': // case Patrol
            // remove the first two useless chars
            line.erase(0, 2); // remove the first two useless chars ("R,")


            // set x to the first number before ','
            x1 = stoi(line.substr(0, line.find(',')));
            // remove the x,
            line.erase(0, line.find(',') + 1);
            // set y to the new first number before ','
            y1 = stoi(line.substr(0, line.find(',')));
            // remove the y,
            line.erase(0, line.find(',') + 1);
            // set toX to the new first number before ','
            x2 = stoi(line.substr(0, line.find(',')));
            // remove the toX,
            line.erase(0, line.find(',') + 1);
            // set toY to the remaining number
            y2 = stoi(line.substr(0, line.find(',')));

            // add to the dynamic object list the new object as an object of type Patrol
            this->objectList->addTail(new Patrol(x1, y1, x2, y2, 50 * difficulty, 20 * difficulty));

            break;

        case 'N':
            line.erase(0, 2); // remove the first two useless chars ("N,")
            x = stoi(line.substr(0, line.find(',')));
            line.erase(0, line.find(',') + 1);
            y = stoi(line.substr(0, line.find(',')));
            line.erase(0, line.find(',') + 1);
            d = stoi(line.substr(0, line.find(',')));
            this->objectList->addTail(
                    new Enemy(x, y, 20 * difficulty, 5 * difficulty, 10 * difficulty, d == 0 ? 'r' : 'l'));
            break;

        default: // none of the previous cases were matched
            wcout << "Invalid encoding: " << line << endl;
    }
}

// draw the skeleton of the map that was read from the file
void Map::drawBaseMap(WINDOW *win, int verticalShift) {
    for (int i = 0; i < OBJECT_TABLE_LENGTH; ++i) {
        mvwaddwstr(win, i + verticalShift, 0, objectTable[i].c_str());
    }
}

// draw the objects contained in the object list
void Map::drawObjects(WINDOW *win, int verticalShift) {
    this->objectList->drawAllObjects(win, verticalShift);
}

// Destructor of the class: delete all pointers
Map::~Map() {
    delete this->objectList;
}

// detect a collision with the wall or with an object, return the type as a char
// and pass the pointer back if the object exists
char Map::detectCollision(int x, int y, pObject &pObj) {
    // first check that it is an exit or entrance
    if (objectTable[y][x] == L'░') {
        return 'E';
    } // then check that it is not colliding with a map "brick"
    else if (objectTable[y][x] != L' ') {
        return 'W';
    }
    // then check that is not colliding with an object
    return objectList->getObjectInPos(x, y, pObj);
}

// remove the object from the objectList
void Map::removeObject(WINDOW *win, pObject pObj) {
    this->objectList->removeElement(pObj);
}

// set the map as the first one: remove the left exit
void Map::setFirstMap() {
    for (int i = 1; i < OBJECT_TABLE_LENGTH - 1; ++i) {
        this->objectTable[i][0] = L'║';
    }
}

void Map::moveObjects(WINDOW *win, int vertical_shift) {
    listObjects tmp = this->objectList->objects;

    pCords cords = nullptr;
    pObject pObj = nullptr;
    char collision;
    bool removeThis = false;

    while (tmp != nullptr) {
        removeThis = false;
        switch (tmp->obj->objectType) {
            case 'R': // case Patrol

                cords = ((pPatrol) tmp->obj)->getNewPos();
                //printw("[%d,%d](%d,%d)",tmp->obj->x,tmp->obj->y,cords->x,cords->y);

                collision = this->detectCollision(cords->x, cords->y, pObj);
                //printw("%c",collision);
                if (collision == ' ' && player->x == cords->x && player->y == cords->y) {
                    collision = 'P';
                } else if (collision == ' ' && player->getWeapon() != nullptr) {
                    if (player->getWeapon()->x == cords->x && player->getWeapon()->y == cords->y)
                        collision = player->getWeapon()->objectType;
                }
                switch (collision) {
                    case 'U':
                        // it's a bullet
                        ((pPatrol) tmp->obj)->life -= ((pBullet) pObj)->getDamage();
                        if (((pPatrol) tmp->obj)->life <= 0) {
                            removeThis = true;
                            progressManager->incrementMoney(50);
                            progressManager->incrementPoints(50);
                        }
                        removeObject(win, pObj);
                        break;
                    case 'P':

                        // it's the player
                        player->receiveDamage(((pPatrol) tmp->obj)->getDamage());
                        removeThis = true;
                        break;
                    case 'F':
                        // it's a shootgun
                        ((pPatrol) tmp->obj)->move(win, cords->x, cords->y);
                        break;
                    case 'G':
                        // it's a gun
                        ((pPatrol) tmp->obj)->move(win, cords->x, cords->y);
                        break;
                    case ' ':
                        // blank space
                        ((pPatrol) tmp->obj)->move(win, cords->x, cords->y);
                        break;
                    case 'V':
                        // it's an enemy bullet
                        removeObject(win, pObj);
                        ((pPatrol) tmp->obj)->move(win, cords->x, cords->y);
                        break;
                    default:
                        // it's an object, we do nothing
                        break;
                }

                delete cords;
                break;
            case 'U': // case Player Bullet
                if (((pBullet) tmp->obj)->range <= 0) {
                    removeThis = true;
                } else {
                    ((pBullet) tmp->obj)->range--;
                    cords = ((pBullet) tmp->obj)->getNewPos();
                    collision = this->detectCollision(cords->x, cords->y, pObj);
                    if (collision == ' ' && player->x == cords->x && player->y == cords->y) {
                        collision = 'P';
                    } else if (collision == ' ' && player->getWeapon() != nullptr) {
                        if (player->getWeapon()->x == cords->x && player->getWeapon()->y == cords->y)
                            collision = player->getWeapon()->objectType;
                    }

                    if (collision == ' ') ((pBullet) tmp->obj)->move(win, cords->x, cords->y);
                    else if (collision == 'B') {
                        ((pBomb) pObj)->life -= ((pBullet) tmp->obj)->getDamage();
                        if (((pBomb) pObj)->life <= 0) {
                            removeObject(win, pObj);
                            progressManager->incrementMoney(20);
                            progressManager->incrementPoints(20);
                        }
                        removeThis = true;
                    } else if (collision == 'R') {
                        ((pPatrol) pObj)->life -= ((pBullet) tmp->obj)->getDamage();
                        if (((pPatrol) pObj)->life <= 0) {
                            removeObject(win, pObj);
                            progressManager->incrementMoney(50);
                            progressManager->incrementPoints(50);
                        }
                        removeThis = true;
                    } else if (collision == 'N') {
                        ((pEnemy) pObj)->life -= ((pBullet) tmp->obj)->getDamage();
                        if (((pEnemy) pObj)->life <= 0) {
                            removeObject(win, pObj);
                            progressManager->incrementMoney(70);
                            progressManager->incrementPoints(70);
                        }
                        removeThis = true;

                    } else if (collision == 'V') {
                        removeObject(win, pObj);
                        removeThis = true;
                    } else removeThis = true;
                    delete cords;
                }
                break;

            case 'N': // case Enemy
                if (rand() % 10 == 0) {
                    //shoot an enemy bullet
                    this->objectList->addTail(
                            new Bullet((pEnemy(tmp->obj))->x, (pEnemy(tmp->obj))->y, (pEnemy(tmp->obj))->getDamage(),
                                       (pEnemy(tmp->obj))->getDirection(), (pEnemy(tmp->obj))->getRange(), false));
                }
                break;

            case 'V': // case Enemy bullet
                if (((pBullet) tmp->obj)->range <= 0) {
                    removeThis = true;
                } else {
                    ((pBullet) tmp->obj)->range--;
                    cords = ((pBullet) tmp->obj)->getNewPos();
                    collision = this->detectCollision(cords->x, cords->y, pObj);
                    if (collision == ' ' && player->x == cords->x && player->y == cords->y) {
                        collision = 'P';
                    }

                    if (collision == ' ') ((pBullet) tmp->obj)->move(win, cords->x, cords->y);
                    else if (collision == 'P') {
                        player->receiveDamage(((pBullet) tmp->obj)->getDamage());
                        removeThis = true;
                    } else removeThis = true;
                    delete cords;
                }
                break;
        }
        if (removeThis) {
            pObject app = tmp->obj;
            tmp = tmp->next;
            this->removeObject(win, app);
        } else {
            tmp = tmp->next;
        }

    }
}

void Map::shootBullet(WINDOW *win, int x, int y, char direction) {
    // player has weapon and it is not stuck on a wall
    if (player->getWeapon() != nullptr && this->objectTable[player->getWeapon()->y][player->getWeapon()->x] == L' ') {
        pObject pObj = nullptr;

        char collision = detectCollision(x, y, pObj);
        collision = this->detectCollision(x, y, pObj);
        if (collision == ' ' && player->x == x && player->y == y) {
            collision = 'P';
        } else if (collision == ' ' && player->getWeapon() != nullptr) {
            if (player->getWeapon()->x == x && player->getWeapon()->y == y)collision = player->getWeapon()->objectType;
        }

        if (collision == ' ') {
            this->objectList->addTail(new Bullet(x, y, player->getWeapon()->getDamage(), direction,
                                                 player->getWeapon()->getRange(), true));
        } else if (collision == 'B') {
            ((pBomb) pObj)->life -= player->getWeapon()->getDamage();
            if (((pBomb) pObj)->life <= 0) {
                removeObject(win, pObj);
                progressManager->incrementMoney(20);
                progressManager->incrementPoints(20);
            }

        } else if (collision == 'R') {
            ((pPatrol) pObj)->life -= player->getWeapon()->getDamage();
            if (((pPatrol) pObj)->life <= 0) {
                removeObject(win, pObj);
                progressManager->incrementMoney(50);
                progressManager->incrementPoints(50);
            }
        } else if (collision == 'N') {
            ((pEnemy) pObj)->life -= player->getWeapon()->getDamage();
            if (((pEnemy) pObj)->life <= 0) {
                removeObject(win, pObj);
                progressManager->incrementMoney(70);
                progressManager->incrementPoints(70);
            }
        } else if (collision == 'V') {
            removeObject(win, pObj);
        }
    }
}
