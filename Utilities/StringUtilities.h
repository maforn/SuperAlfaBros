//
// Created by vboxuser on 26.01.23.
//

#ifndef SUPERALFABROS_STRINGUTILITIES_H
#define SUPERALFABROS_STRINGUTILITIES_H

#include <string>
using namespace std;

// formatter for the player status strings (life and armour)
// concatenates label and value, adding additional spaces until a total length of labelLength
// then adds (value/step) icons at the end of the string (CONSIDERING ONLY INTEGER PART OF value/step)
// returns the string obtained this way
wstring playerStatusFormatter(wstring label, int labelLength, int value, int step);

// formatter for the progress strings (money and points)
// modifies label(i) by adding val(i) at the end of it (for i in {1, 2})
// if val(k) has less digits than val(h), spaces are added between label(k) and val(k)
// example of label1 and label2 after calling progressFormatter("money  > ", "points > ", 1234, 1):
// label1 =     money  > 1234
// label2 =     points >    1 <- added spaces
void progressFormatter(wstring& label1, wstring& label2, int val1, int val2);

//copies count strings from sources to dest
void copyStrings(wstring source[], wstring dest[], int count);

#endif //SUPERALFABROS_STRINGUTILITIES_H
