//
// Created by matteo on 23/11/2022.
//

#include "DynamicObjectList.hpp"

// the struct must contain a superclass object, type that will help get the subclass and the next and previous objects


// initiate the pointer to null
DynamicObjectList::DynamicObjectList() {
    this->objects = nullptr;
}

// add element to the tail of the list
void DynamicObjectList:: addTail(pObject pObj) {
    listObjects tmp = new listObject;
    tmp->next = nullptr;
    tmp->obj = pObj;
    if (this->objects == nullptr) {
        this->objects = tmp;
    } else {
        listObjects iter = this->objects;
        while (iter->next != nullptr) {
            iter = iter->next;
        }
        iter->next = tmp;
    }
}

// draw all the objects
void DynamicObjectList::drawAllObjects(WINDOW *win, int verticalShift) {
    // iterate all object
    listObjects iterator = this->objects;
    while (iterator != nullptr) {
        // draw them at the specified x, y
        mvwaddwstr(win, iterator->obj->y + verticalShift, iterator->obj->x, iterator->obj->drawing.c_str());
        iterator = iterator->next;
    }
}

// Precondition: not called on an empty list
// remove an element from the list
void DynamicObjectList::removeElement(pObject obj) {
    listObjects iterator = this->objects;
    // if it's the first object just remove it
    if (obj == iterator->obj) {
        this->objects = iterator->next;
        delete iterator;
    } else {
        // iterate until the right object is found
        listObjects prev = iterator;
        iterator = iterator->next;
        while (iterator->obj != obj) {
            prev = iterator;
            iterator = iterator->next;
        }
        prev->next = iterator->next;
        delete iterator;
    }

}

// Destructor of the class: delete free pointers
DynamicObjectList::~DynamicObjectList() {
    listObjects tmp;
    while (this->objects != nullptr) {
        tmp = this->objects;
        this->objects = this->objects->next;
        delete tmp;
    }
}

// if it exists, get the object in x, y and return the type while setting the pointer to the object
char DynamicObjectList::getObjectInPos(int x, int y, pObject &pObj) {
    listObjects iterator = this->objects;
    // iterate the object list
    while (iterator != nullptr) {
        // if an object is found return the objectType and set the pointer to the object
        if (iterator->obj->y == y && iterator->obj->x == x) {
            pObj = iterator->obj;
            return iterator->obj->objectType;
        }
        iterator = iterator->next;
    }
    // if no collision was found the player can move there
    return ' ';
}
