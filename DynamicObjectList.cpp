//
// Created by admin on 23/11/2022.
//

#include "DynamicObjectList.hpp"

// the struct must contain a superclass object, type that will help get the subclass and the next and previous objects
struct DynamicObjectList::listObject {
    Object *obj;
    char type;
    listObject *next;
    listObject *prev;
};

DynamicObjectList::DynamicObjectList() {
    this->objects = nullptr;
}

void DynamicObjectList::addTail(pObject pObj, char type) {
    listObjects tmp = new listObject;
    tmp->type = type;
    tmp->next = nullptr;
    tmp->prev = nullptr;
    tmp->obj = pObj;
    if (this->objects == nullptr) {
        this->objects = tmp;
    } else {
        listObjects iter = this->objects;
        while (iter->next != nullptr) {
            iter = iter->next;
        }
        tmp->prev = iter;
        iter->next = tmp;
    }
}

void DynamicObjectList::addHead(pObject pObj, char type) {
    listObjects tmp = new listObject;
    tmp->type = type;
    tmp->next = nullptr;
    tmp->prev = nullptr;
    tmp->obj = pObj;
    if (this->objects == nullptr) {
        this->objects = tmp;
    } else {
        tmp->next = this->objects;
        this->objects->prev = tmp;
        this->objects = tmp;
    }
}