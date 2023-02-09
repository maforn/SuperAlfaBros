//
// Created by enrico on 03/01/23.
//

#include "Patrol.hpp"

Patrol::Patrol(int x, int y, int toX, int toY, int life, int damage) : Object(x, y, L"🚨", 'R') {
    this->x2 = toX;
    this->y2 = toY;
    this->x1 = x;
    this->y1 = y;
    this->direction = true;
    this->damage = damage;
    this->life = life;
}

void Patrol::drawPatrol(WINDOW *win) {

    mvwaddwstr(win, this->y, this->x, this->drawing.c_str());
}


 void Patrol::move(int x, int y) {
    this->x=x;
    this->y=y;
}

pCords Patrol::getNewPos() {

    pCords cords = new Cords;
    cords->x = this->x;
    cords->y = this->y;
    if ((this->x == this->x1 && this->y == this->y1) || (this->x == this->x2 && this->y == this->y2) ){
        // change direction
        this->direction = !this->direction;
    }
    if (this->direction){
        // go to x1,y1
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
        // go to x2,y2
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


