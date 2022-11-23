//
// Created by matteo on 23/11/2022.
//
#include "Map.hpp"


int main () {
    Map *m = new Map(R"(C:\Users\admin\Desktop\Uni\Programmazione\Progetto\SuperAlfaBros\map.map)");

    for (int i = 0; i < 30; ++i) {
        cout << m->objectTable[i] << endl;
    }

    return 0;
}