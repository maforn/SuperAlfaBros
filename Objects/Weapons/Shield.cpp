//
// Created by enrico on 26/01/23.
//

#include "Shield.hpp"

Shield::Shield(int x, int y, int level) : Weapon(x, y, level, 0, L")", 'w', L")", L"(") {
    life = level*2;
}
int Shield::getLife(){
    return life;
}
void Shield::setLife(int life){
    this->life = life;
}
void Shield::receiveDamage(int damage){
    life -= damage;
}