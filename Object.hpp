//
// Created by matteo on 23/11/2022.
//

#ifndef SUPERALFABROS_OBJECT_HPP
#define SUPERALFABROS_OBJECT_HPP


class Object {
protected:

public:
    int x;
    int y;
    char drawing;
    char objectType;
    Object(int x, int y, char drawing, char objectType);
};

typedef Object* pObject;

#endif //SUPERALFABROS_OBJECT_HPP
