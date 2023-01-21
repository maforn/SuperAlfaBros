//
// Created by enrico on 03/01/23.
//

#include "Patrol.hpp"

Patrol::Patrol(int x, int y, int x1, int y1, int x2, int y2) : Object(x, y, L"🚨", 'R') {
    this->x2 = x2;
    this->y2 = y2;
    this->x1 = x1;
    this->y1 = y1;
    this->direction = true;
}

void Patrol::drawPatrol(WINDOW *win) {
    mvwaddwstr(win, this->y, this->x, this->drawing.c_str());
}

void Patrol::movePatrol() {
    if ((this->x == this->x1 && this->y == this->y1) || (this->x == this->x2 && this->y == this->y2) ){
        // cambia direzione
        this->direction = !this->direction;
    } else if (this->direction){
        // vai verso x1,y1
        if (this->x < this->x1){
            this->x++;
        } else if (this->x > this->x1){
            this->x--;
        } else if (this->y < this->y1){
            this->y++;
        } else if (this->y > this->y1){
            this->y--;
        }
    } else {
        // vai verso x2,y2
        if (this->x < this->x2){
            this->x++;
        } else if (this->x > this->x2){
            this->x--;
        } else if (this->y < this->y2){
            this->y++;
        } else if (this->y > this->y2){
            this->y--;
        }
    }
}

void Patrol::movePatrolThread() {
    while (true){
        this->movePatrol();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}
