//
// Created by admin on 24/11/2022.
//

#include "Player.hpp"

bool Player::incrementField(int& field, int incr, const int maxVal){
    if(field >= maxVal)
        return false;
    else{
        if(field + incr <= maxVal)
            field += incr;
        else
            field = maxVal;
        return true;
    }
}

//PUBLIC

// Constructor of the class: will set the new vars and use the constructor of the superclass with '0' as drawing and 'P'
// as object type
Player::Player(int x, int y, int life): Object(x,y, L"0", 'P') {
    this->life = life;
    this->armour = armour;
    this->damage = 0;
}

// calculate damage scaled on the level TODO: use a decent equation
int Player::calculateDamage() {
    return this->life / 2;
}

// draw the player on a screen
void Player::drawPlayer(WINDOW *win, int verticalShift) {
    mvwaddwstr(win, this->y + verticalShift, this->x, this->drawing.c_str());
}

// damage the player of a certain amount
void Player::receiveDamage(int dmg) {
    if(this->armour > 0){
        double reducedByArmour = (int)((double)(this->armour) / 100 * dmg);
        dmg -= reducedByArmour;

        if(this->armour >= reducedByArmour)
            this->armour -= reducedByArmour;
        else
            this->armour = 0;
    }

    this->life -= dmg;
}

int Player::getLife() {
    return this->life;
}

int Player::getArmour(){
    return this->armour;
}

int Player::getDamage(){
    return this->damage;
}

bool Player::incrementLife(int incr){
    return incrementField(this->life, incr, MAX_LIFE);
}

bool Player::incrementArmour(int incr){
    return incrementField(this->armour, incr, MAX_ARMOUR);
}

void Player::changeDamage(int newVal) {
    this->damage = newVal;
}

void Player::changeSkin(std::wstring newSkin){
    this->drawing = newSkin;
}