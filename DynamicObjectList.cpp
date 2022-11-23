//
// Created by admin on 23/11/2022.
//

#include "DynamicObjectList.hpp"

struct DynamicObjectList::listObject {
    Object *obj;
    listObject *next;
    listObject *prev;
};

DynamicObjectList::DynamicObjectList() {
    this->objects = NULL;
}

void DynamicObjectList::add_tail(pObject pObj) {
    listObjects tmp = new listObject;
    tmp->next = NULL;
    tmp->prev = NULL;
    tmp->obj = pObj;
    if (this->objects == NULL) {
        this->objects = tmp;
    } else {
        listObjects iter = this->objects;
        while (iter->next != NULL) {
            iter = iter->next;
        }
        tmp->prev = iter;
        iter->next = tmp;
    }
}

void DynamicObjectList::add_head(pObject pObj) {
    listObjects tmp = new listObject;
    tmp->next = NULL;
    tmp->prev = NULL;
    tmp->obj = pObj;
    if (this->objects == NULL) {
        this->objects = tmp;
    } else {
        tmp->next = this->objects;
        this->objects->prev = tmp;
        this->objects = tmp;
    }
}