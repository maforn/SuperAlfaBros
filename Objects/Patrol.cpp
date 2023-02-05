//
// Created by enrico on 03/01/23.
//

#include "Patrol.hpp"

Patrol::Patrol(int x, int y, int toX, int toY, int damage) : Object(x, y, L"🚨", 'R') {
    this->x2 = toX;
    this->y2 = toY;
    this->x1 = x;
    this->y1 = y;
    this->direction = true;
    this->damage = damage;
}

void Patrol::drawPatrol(WINDOW *win) {

    mvwaddwstr(win, this->y, this->x, this->drawing.c_str());
}


 void Patrol::move(WINDOW *win, int x, int y) {
     //printw("%ls",this->drawing.c_str());
     mvwaddwstr(win, this->y, this->x , L" ");
    this->x=x;
    this->y=y;
     mvwaddwstr(win, y, x, this->drawing.c_str());
}

pCords Patrol::getNewPos() {

    pCords cords = new Cords;
    cords->x = this->x;
    cords->y = this->y;
    if ((this->x == this->x1 && this->y == this->y1) || (this->x == this->x2 && this->y == this->y2) ){
        // cambia direzione
        this->direction = !this->direction;
    }
    if (this->direction){
        // vai verso x1,y1
        if (this->x < this->x1){
            cords->x = this->x+1;
        } else if (this->x > this->x1){
            cords->x = this->x-1;
        } else if (this->y < this->y1){
            cords->y = this->y+1;
        } else if (this->y > this->y1){
            cords->y = this->y-1;
        }
    } else {
        // vai verso x2,y2
        if (this->x < this->x2){
            cords->x = this->x+1;
        } else if (this->x > this->x2){
            cords->x = this->x-1;
        } else if (this->y < this->y2){
            cords->y = this->y+1;
        } else if (this->y > this->y2){
            cords->y = this->y-1;
        }
    }
    return cords;
}

int Patrol::getDamage() {
    return this->damage;
}


