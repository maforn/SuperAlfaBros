//
// Created by admin on 24/11/2022.
//

#include "Player.hpp"

// Constructor of the class: will set the new vars and use the constructor of the superclass with '0' as drawing and 'P'
// as object type
Player::Player(int x, int y, int life): Object(x,y, L"0", 'P') {
    this->life = life;
    weapon = nullptr;
}

// calculate damage scaled on the level TODO: use a decent equation
int Player::calculateDamage() {
    return this->life / 2;
}

// draw the player on a screen
void Player::drawPlayer(WINDOW *win) {
    mvwaddwstr(win, this->y, this->x, this->drawing.c_str());
    if (this->weapon != nullptr) {
        this->weapon->draw(win);
    }
}

// damage the player of a certain amount
void Player::receiveDamage(int dmg) {
    this->life -= dmg;
}

int Player::getLife() {
    return this->life;
}

pWeapon Player::getWeapon() {
    return this->weapon;
}

void Player::setWeapon(Weapon *newWeapon) {
    this->weapon = newWeapon;
}

void Player::useWeaponRight(WINDOW *win) {
    if (weapon != nullptr) {
        weapon->useRight(win);
    }
}

void Player::useWeaponLeft(WINDOW *win) {
    if (weapon != nullptr) {
        weapon->useLeft(win);
    }
}

void Player::movePlayer(WINDOW *win, int x, int y) {
    mvwaddwstr(win, this->y, this->x, L" ");
    if (this->weapon != nullptr) {
        if (this->x < x) {
            this->weapon->pointRight();
        } else if (this->x > x) {
            this->weapon->pointLeft();
        }

        this->weapon->moveWeapon(win, this->weapon->isRight ? x + 1 : x - 1, y);

    }
    this->x = x;
    this->y = y;

    this->drawPlayer(win);
}

void Player::removeWeapon() {
    delete this->weapon;
    this->weapon = nullptr;
}

pWeapon Player::changeWeapon(pWeapon newWeapon) {
    pWeapon oldWeapon = this->weapon;
    this->weapon = newWeapon;
    return oldWeapon;
}
