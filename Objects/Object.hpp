//
// Created by matteo on 23/11/2022.
//

#ifndef SUPERALFABROS_OBJECT_HPP
#define SUPERALFABROS_OBJECT_HPP

#include <string>
#include <ncurses.h>

struct Cords {
    int x;
    int y;
};
typedef Cords *pCords;

// the standard superclass for any object created in the map
class Object {
public:
    // x coordinates
    int x;
    // y coordinates
    int y;
    // which char will be drawn on the screen
    std::wstring drawing;
    // which kind of subclass it is (stored as a char), for example T for teleporter
    char objectType;
    // Constructor of the class: will set all the variables as specified
    Object(int x, int y, std::wstring drawing, char objectType);
    //virtual void getNewPos(int &x, int &y);
    //virtual void move(WINDOW *win, int x, int y);
    void draw(WINDOW *win);
};

// set a name for the pointer to the class Object
typedef Object* pObject;

#endif //SUPERALFABROS_OBJECT_HPP
