//
// Created by vboxuser on 23.01.23.
//

#ifndef SUPERALFABROS_REFILLLIST_HPP
#define SUPERALFABROS_REFILLLIST_HPP

#include <string>
using namespace std;

class RefillList{
protected:

    // struct to represent refills and definition of pointer type
    struct refill;
    typedef refill* p_refill;

    // pointer to the head of the list
    p_refill head;

    // returns a pointer to the refill with the specified code. Returns NULL if such refill is not found.
    p_refill findRefill(char code);

    // returns a pointer to the refill in position=index in the list. Returns NULL if such refill is not found.
    p_refill findRefillByIndex(int index);

    // inserts element at the end of the list starting with head and returns the new head
    p_refill tailInsert(p_refill head, p_refill element);

public:

    //constructor: initializes an empty list
    RefillList();

    // adds a refill with the specified attributes at the end of the list
    void addRefill(char code, wstring name, int amount, int startingPrice);

    // set the actual price of each refill to its starting price * multiplier
    void multiplyPrices(double multiplier);

    // returns the number of refills in the list
    int getCount();

    // returns the code of the refill in position=index in the list. Returns / if such refill is not found
    char getCodeByIndex(int index);

    // returns the price of the refill with the specified code. Returns -1 if such refill is not found
    int getPrice(char code);

    // returns the amount of the refill with the specified code. Returns -1 if such refill is not found
    int getAmount(char code);

    // generates strings containing the refills values and inserts them into dest
    // count indicates the maximum number of strings to insert into dest
    void getRefillInfoStrings(wstring dest[], int count);
};


#endif //SUPERALFABROS_REFILLLIST_HPP
