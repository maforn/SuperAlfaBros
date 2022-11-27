//
// Created by admin on 24/11/2022.
//

#include "Player.hpp"

// Constructor of the class: will set the new vars and use the constructor of the superclass with '0' as drawing and 'P'
// as object type
Player::Player(int x, int y, int life): Object(x,y, L"0", 'P') {
    this->life = life;
}

// calculate damage scaled on the level TODO: use a decent equation
int Player::calculateDamage() {
    return this->life / 2;
}

// draw the player on a screen
void Player::drawPlayer(WINDOW *win) {
    printf("%d - %d\n", this->y, this->x);
    mvwaddwstr(win, this->y, this->x, this->drawing.c_str());
}

// damage the player of a certain amount
void Player::receiveDamage(int dmg) {
    this->life -= dmg;
    if (this->life <= 0) {
        //TODO: GAMEOVER
    }
}
