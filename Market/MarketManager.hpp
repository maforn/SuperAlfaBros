//
// Created by vboxuser on 23.01.23.
//

#ifndef SUPERALFABROS_MARKETMANAGER_HPP
#define SUPERALFABROS_MARKETMANAGER_HPP

#include "MarketDisplayer.hpp"

#define NUMBER_OF_PAGES 4

class MarketManager{
protected:

    // displayer for the market
    MarketDisplayer displayer;

    // lists of market items
    RefillList refills;
    WeaponList weapons;
    SkinList skins;

    // pointers to Player and ProgressManager objects
    Player* player;
    ProgressManager* progressManager;

    // functions to initialize market items. One for each type of item
    void initializeRefills();
    void initializeWeapons();
    void initializeSkins();

    // function to initialize market displayer
    void initializeDisplayer();

    // functions to purchase and award a refill of a given code
    void purchaseRefill(char code);
    bool awardRefill(char code);

    // functions to purchase and award a skin of a given code
    void purchaseSkin(char code);
    void activateSkin(char code); // called by purchaseSkin if skin is already unlocked
    void unlockSkin(char code, int price); // called by purchaseSkin to unlock a new skin

    // functions to purchase and award a weapon of a given code
    void purchaseWeapon(char code);
    void activateWeapon(char code); //called by purchaseWeapon if weapon is already unlocked
    void unlockWeapon(char code, int price); // called by purchaseWeapon to unlock a new weapon

    // functions to execute the user choice, depending on the page the choice was made in
    void executeChoice(int choice);
    void executeMainPageChoice(int choice);
    void executeRefillPageChoice(int choice);
    void executeWeaponPageChoice(int choice);
    void executeSkinPageChoice(int choice);

    // function to go back to market main page. Must be called before reloading market display
    void back();

    // returns true if the user chose to exit market
    bool isExitChosen(int choice);

    // returns true if the user chose to quit game
    bool isQuitChosen(int choice);

public:

    //Constructor: initializes the market items and the pointer to the Player and ProgressManager objects
    MarketManager(Player* player, ProgressManager* progressManager);

    // returns the drawing of the skin of the specified code
    wstring getSkin(char code);

    pWeapon getWeapon(char code);

    // unlock all weapons whose codes appear in codeStr
    void addUnlockedWeapons(string codeStr);
    // unlock all skins whose codes appear in codeStr
    void addUnlockedSkins(string codeStr);

    // function to open the market in window win, starting from (start_x, start_y)
    void openMarket(WINDOW* win, int start_y, int start_x);

    // the function should be called when the user has to make choices within the market.
    // the function returns only when the user chooses to exit the market or quit the game.
    // the function returns false if the user decides to quit the game.
    bool waitForMarketClosure();
};

#endif //SUPERALFABROS_MARKETMANAGER_HPP