//
// Created by vboxuser on 26.01.23.
//

#include "StringUtilities.h"

wstring playerStatusFormatter(wstring label, int labelLength, int value, int step){
    label += to_wstring(value);
    int lenDiff = labelLength - label.length();
    for(int i = 0; i < lenDiff; i++)
        label += L" ";

    int iconCount = value / step;
    for(int i = 0; i < iconCount; i++)
        label += L"■ ";

    return label;
}

void progressFormatter(wstring& label1, wstring& label2, int val1, int val2){
    wstring str1 = to_wstring(val1);
    wstring str2 = to_wstring(val2);

    int lenDiff = str1.length() - str2.length();
    for(int i = 0; i < -lenDiff; i++)
        label1 += L" ";
    for(int i = 0; i < lenDiff; i++)
        label2 += L" ";

    label1 += str1;
    label2 += str2;
}

void copyStrings(wstring source[], wstring dest[], int count) {
    for(int i = 0; i < count; i++)
        dest[i] = source[i];
}