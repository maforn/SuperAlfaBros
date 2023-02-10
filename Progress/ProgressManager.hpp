//
// Created by vboxuser on 23.01.23.
//

/*
 * This class handles progress in the current game as well as over all games played.
 * Progress in the current game consists of money acquired, points scored and the level of difficulty reached.
 * Progress over all played games consists of skins purchased, weapons purchased and the amount of armour
 * remaining at the end of the previous game. This data is saved on .txt files. Armour is saved as an integer;
 * whereas skins and weapons are saved as a string composed of the codes associated to the unlocked skins and weapons.
 */

#ifndef SUPERALFABROS_PROGRESSMANAGER_HPP
#define SUPERALFABROS_PROGRESSMANAGER_HPP

#include <string>
#include <fstream>
#include "CodeList.hpp"
using namespace std;

class ProgressManager{
protected:

    // names of the files to use for progress saving and loading
    string playerFileName, weaponFileName, skinFileName;

    // variables for current game progress
    int money;
    int points;

    // difficulty is a multiplier derived from the current points and the number of unlocked weapons
    // all game objects requiring incremental difficulty should have their values multiplied by difficulty
    double difficulty;

    // variables for overall player progress across all played games
    int armour; // saved armour value
    CodeList skinData; // list of the codes of the skins that have been unlocked
    CodeList weaponData; // list of the codes of the weapons that have been unlocked

    // loads the saved data regarding player status, ie armour
    void loadPlayerData();

    // adds to dest the defaultCode and the codes saved in the file fileName
    void loadCodeData(CodeList& dest, string fileName, char defaultCode);

    // saves data regarding player status
    void savePlayerData();

    // saves the codes in source into the file fileName
    void saveCodeData(CodeList source, string fileName);

    // calculates the game difficulty based on unlocked weapons and money
    void calculateDifficulty();

public:

    // constructor: initializes file names
    ProgressManager(string playerFileName, string weaponFileName, string skinFileName);

    // loads all the saved data
    void loadSavedData();

    // saves all progress made
    void saveProgress();

    // functions to get a string composed of the codes of the unlocked weapons/skins
    string getUnlockedWeaponsString();
    string getUnlockedSkinsString();

    // functions to unlock the weapon/skin with the specified code
    void unlockNewWeapon(char code);
    void unlockNewSkin(char code);

    // functions to change the current weapon/skin to the one with the specified code
    void changeCurrentWeapon(char code);
    void changeCurrentSkin(char code);

    // functions to get the code of the current weapon/skin
    char getCurrentWeaponCode();
    char getCurrentSkinCode();

    // returns the saved value for the armour
    int getSavedArmour();
    // updates the saved value for the armour to newArmour and saves it to file
    void updateArmour(int newArmour);

    // returns the current amount of money
    int getMoney();
    // increments the current amount of money by incr
    void incrementMoney(int incr);

    // returns the current points
    int getPoints();
    // increments the current points by incr
    void incrementPoints(int incr);

    // returns the difficulty for the current game
    double getDifficulty();
};

typedef ProgressManager* pProgressManager;

#endif //SUPERALFABROS_PROGRESSMANAGER_HPP
