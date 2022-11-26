//
// Created by admin on 23/11/2022.
//

#ifndef SUPERALFABROS_DYNAMICOBJECTLIST_HPP
#define SUPERALFABROS_DYNAMICOBJECTLIST_HPP

#include "../Objects/Object.hpp"
#include <ncurses.h>

// create a class for the dynamic object list that will manage all the objects of a level
class DynamicObjectList {
private:
    // create a struct for the dynamic list of objects
    struct listObject;
    // define the pointer to the struct
    typedef listObject *listObjects;
    // create a pointer to the list of objects
    listObjects objects;
public:
    // Constructor of the class: does actually nothing
    DynamicObjectList();

    // draw all the objects
    void drawAllObjects(WINDOW *win);

    // add an element to the list
    void addTail(pObject pObj);
    void addHead(pObject pObj);

    // remove an element from the list
    void removeElement(pObject obj);

    // if exists, get the object in x, y and return the type while setting the pointer
    char getObjectInPos(int x, int y, pObject &pObj);

    // Destructor of the class: delete free pointers
    ~DynamicObjectList();
};

// set a name for the pointer to the class DynamicObjectList
typedef DynamicObjectList *pDynamicObjectList;


#endif //SUPERALFABROS_DYNAMICOBJECTLIST_HPP
