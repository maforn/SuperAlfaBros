//
// Created by admin on 23/11/2022.
//

#include "DynamicObjectList.hpp"

// the struct must contain a superclass object, type that will help get the subclass and the next and previous objects
struct DynamicObjectList::listObject {
    Object *obj;
    listObject *next;
};

DynamicObjectList::DynamicObjectList() {
    this->objects = nullptr;
}

void DynamicObjectList::addTail(pObject pObj) {
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

void DynamicObjectList::addHead(pObject pObj) {
    listObjects tmp = new listObject;
    tmp->next = nullptr;
    tmp->obj = pObj;
    if (this->objects == nullptr) {
        this->objects = tmp;
    } else {
        tmp->next = this->objects;
        this->objects = tmp;
    }
}

// draw all the objects
void DynamicObjectList::drawAllObjects(WINDOW *win) {
    listObjects iterator = this->objects;
    while (iterator != nullptr) {
        mvwaddwstr(win, iterator->obj->y, iterator->obj->x, iterator->obj->drawing.c_str());
        iterator = iterator->next;
    }
}

// Precondition: not called on an empty array
void DynamicObjectList::removeElement(pObject obj) {
    listObjects iterator = this->objects;
    if (obj == iterator->obj) {
        this->objects = iterator->next;
        delete iterator;
    } else {
        listObjects prev = iterator;
        iterator = iterator->next;
        while (iterator->obj != obj) {
            prev = iterator;
            iterator = iterator->next;
        }
        prev = iterator->next;
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

char DynamicObjectList::getObjectInPos(int x, int y, pObject &pObj) {
    listObjects iterator = this->objects;
    while (iterator != nullptr) {
        if (iterator->obj->y == y && iterator->obj->x == x) {
            pObj = iterator->obj;
            return iterator->obj->objectType;
        }
        iterator = iterator->next;
    }
    return ' ';
}
