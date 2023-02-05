//
// Created by vboxuser on 23.01.23.
//

#ifndef SUPERALFABROS_SKINLIST_HPP
#define SUPERALFABROS_SKINLIST_HPP

#include <string>
using namespace std;

class SkinList{
protected:

    // struct to represent skins and definition of pointer type
    struct skin;
    typedef skin* p_skin;

    //pointer to the head of the list
    p_skin head;

    // returns a pointer to the skin with the specified code. Returns NULL if such skin is not found.
    p_skin findSkin(char code);

    // returns a pointer to the skin in position=index in the list. Returns NULL if such skin is not found.
    p_skin findSkinByIndex(int index);

    // inserts element at the end of the list starting with head and returns the new head
    p_skin tailInsert(p_skin head, p_skin element);

    // inserts element at the beginning of the list starting with head and returns the new head
    p_skin headInsert(p_skin head, p_skin element);

    // skips the skin with the specified code in the list starting with head (NO DELETION) and returns the new head
    p_skin skipSkin(p_skin head, char code);

public:

    // constructor: initializes an empty list
    SkinList();

    // adds a skin with the specified attributes at the end of the list
    void addSkin(char code, wstring drawing, wstring name, int price);

    // returns the number of skins in the list
    int getCount();

    // returns the code of the skin in position=index in the list. Returns / if such skin is not found
    char getCodeByIndex(int index);

    // sets the price of the skin with the specified code to zero
    void removePrice(char code);

    // sorts skins by putting those with price = 0 at the beginnig of the list
    void sortSkins();

    // returns the price of the skin with the specified code. Returns -1 if such skin is not found
    int getPrice(char code);

    // returns the price of the skin with the specified code. Returns -1 if such skin is not found
    wstring getDrawing(char code);

    // moves the skin with the specified code at the beginning of the list
    void moveToFirst(char code);

    // generates strings containing the skins values and inserts them into dest
    // count indicates the maximum number of strings to insert into dest
    // selectedCode indicates the code of the skin whose string must contain the label "Selected"
    void getSkinInfoStrings(wstring dest[], int count, char selectedCode);
};


#endif //SUPERALFABROS_SKINLIST_HPP
