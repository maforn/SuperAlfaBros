//
// Created by admin on 23/11/2022.
//

#ifndef SUPERALFABROS_DYNAMICOBJECTLIST_HPP
#define SUPERALFABROS_DYNAMICOBJECTLIST_HPP

#include <cstdlib>
#include "Object.hpp"

class DynamicObjectList {
private:
    struct listObject;
    typedef listObject *listObjects;
    listObjects objects;
public:
    /** Initialize your data structure here. */
    DynamicObjectList();

    /** Inserts a word into the trie. */
    void add_tail(pObject pObj);
    void add_head(pObject pObj);
};

typedef DynamicObjectList *pDynamicObjectList;


#endif //SUPERALFABROS_DYNAMICOBJECTLIST_HPP
