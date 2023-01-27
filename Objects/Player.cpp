//
// Created by admin on 24/11/2022.
//

#include "Player.hpp"

// Constructor of the class: will set the new vars and use the constructor of the superclass with '0' as drawing and 'P'
// as object type
Player::Player(int x, int y, int life): Object(x,y, L"0", 'P') {
    this->life = life;
    pWeapon = nullptr;
}

// calculate damage scaled on the level TODO: use a decent equation
int Player::calculateDamage() {
    return this->life / 2;
}

// draw the player on a screen
void Player::drawPlayer(WINDOW *win) {
    mvwaddwstr(win, this->y, this->x, this->drawing.c_str());
    if (this->pWeapon != nullptr) {
        this->pWeapon->draw(win);
    }
}

// damage the player of a certain amount
void Player::receiveDamage(int dmg) {
    this->life -= dmg;
}

int Player::getLife() {
    return this->life;
}

Weapon *Player::getWeapon() {
    return this->pWeapon;
}

void Player::setWeapon(Weapon *pWeapon) {
    this->pWeapon = pWeapon;
}

void Player::useWeaponRight(WINDOW *win) {
    if (pWeapon != nullptr) {
        pWeapon->useRight(win);
    }
}

void Player::useWeaponLeft(WINDOW *win) {
    if (pWeapon != nullptr) {
        pWeapon->useLeft(win);
    }
}

void Player::movePlayer(WINDOW *win, int x, int y) {
    mvwaddwstr(win, this->y, this->x, L" ");
    if (this->pWeapon != nullptr) {
        if (this->x < x) {
            this->pWeapon->pointRight();
        } else if (this->x > x) {
            this->pWeapon->pointLeft();
        }

        this->pWeapon->moveWeapon(win, this->pWeapon->isRight ? x + 1 : x - 1, y);

    }
    this->x = x;
    this->y = y;

    this->drawPlayer(win);
}