//
// Created by vboxuser on 23.01.23.
//

#include "ProgressManager.hpp"

void ProgressManager::loadPlayerData(){
    ifstream inputFile;
    inputFile.open(this->playerFileName);

    if(inputFile.is_open()){
        string line;
        getline(inputFile, line);
        this->armour = stoi(line);
        inputFile.close();
    }
    else
        this->armour = 0;
}

void ProgressManager::loadCodeData(CodeData& dest, string fileName, char defaultCode){
    dest = CodeData();
    ifstream inputFile;
    inputFile.open(fileName);

    if(inputFile.is_open()){
        string line;
        getline(inputFile, line);
        for(int i = 0; i < line.length(); i++)
            dest.addCode(line[i]);
    }
    dest.addCode(defaultCode);
}

void ProgressManager::savePlayerData(){
    ofstream outputFile;
    outputFile.open(this -> playerFileName);
    outputFile << this->armour;
    outputFile.close();
}

void ProgressManager::saveCodeData(CodeData source, string fileName){
    ofstream outputFile;
    outputFile.open(fileName);
    outputFile << source.getCodesString();
    outputFile.close();
}

void ProgressManager::calculateDifficulty(){
    const double INCR_PER_100_POINTS = 0.1;
    double pointsIncr = INCR_PER_100_POINTS * (this->points / 100);

    const double INCR_PER_WEAPON = 0.3;
    double weaponIncr = INCR_PER_WEAPON * getUnlockedWeaponsString().length();

    this->difficulty = 2 + pointsIncr + weaponIncr;
}

//public

ProgressManager::ProgressManager(const string playerFileName, const string weaponFileName, const string skinFileName){
    this->playerFileName = playerFileName;
    this->weaponFileName = weaponFileName;
    this->skinFileName = skinFileName;

    this->points = 0;
    this->money = 0;
    this->armour = 0;
    this->difficulty = 1;
}

void ProgressManager::loadSavedData(){
    loadPlayerData();
    loadCodeData(this->weaponData, this->weaponFileName, 'A');
    loadCodeData(this->skinData, this->skinFileName, 'A');

    calculateDifficulty();
}

int ProgressManager::getSavedArmour(){
    return(this->armour);
}

void ProgressManager::updateArmour(int newArmour){
    this->armour = newArmour;
    savePlayerData();
}

string ProgressManager::getUnlockedWeaponsString(){
    return ((this->weaponData).getCodesString());
}

void ProgressManager::unlockNewWeapon(char code){
    (this->weaponData).addCode(code);
    saveCodeData(this->weaponData, this->weaponFileName);
}

void ProgressManager::changeCurrentWeapon(char code){
    (this->weaponData).selectCode(code);
    saveCodeData(this->weaponData, this->weaponFileName);
}

char ProgressManager::getCurrentWeaponCode() {
    return((this->weaponData).getCurrentCode());
}

string ProgressManager::getUnlockedSkinsString(){
    return ((this->skinData).getCodesString());
}

void ProgressManager::unlockNewSkin(char code){
    (this->skinData).addCode(code);
    saveCodeData(this->skinData, this->skinFileName);
}

void ProgressManager::changeCurrentSkin(char code){
    (this->skinData).selectCode(code);
    saveCodeData(this->skinData, this->skinFileName);
}

char ProgressManager::getCurrentSkinCode() {
    return((this->skinData).getCurrentCode());
}

double ProgressManager::getDifficulty(){
    return (this->difficulty);
}

int ProgressManager::getMoney(){
    return(this->money);
}
void ProgressManager::incrementMoney(int incr){
    this->money += incr;
}

int ProgressManager::getPoints(){
    return(this->points);
}
void ProgressManager::incrementPoints(int incr){
    this->points += incr;
}