//
// Created by admin on 23/11/2022.
//

#ifndef SUPERALFABROS_DYNAMICOBJECTLIST_HPP
#define SUPERALFABROS_DYNAMICOBJECTLIST_HPP

#include "../Objects/Object.hpp"

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

    // add elements to the list
    void addTail(pObject pObj);
    void addHead(pObject pObj);
};

// set a name for the pointer to the class DynamicObjectList
typedef DynamicObjectList *pDynamicObjectList;


#endif //SUPERALFABROS_DYNAMICOBJECTLIST_HPP
