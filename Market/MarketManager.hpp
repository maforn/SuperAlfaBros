//
// Created by vboxuser on 23.01.23.
//

/*
 * This class manages the market.
 *
 * There are three types of market items: refills, weapons and skins. Each type is implemented by a list
 * (RefillList, WeaponItemList, SkinList).
 *
 * MarketDisplay has a pointer to the Player instance so that purchased items can be awarded.
 * It also has a pointer to the ProgressManager, allowing it to access/check/decrement money, save purchased items
 * and retrieve the difficulty level. The difficulty level is used to progressively increase market items prices.
 *
 * The MarketManager processes and executes the choices made by the user within the market, but doesn't
 * display the market itself. Market display is handled by the displayer (instance of MarketDisplayer).
 */

#ifndef SUPERALFABROS_MARKETMANAGER_HPP
#define SUPERALFABROS_MARKETMANAGER_HPP

#include "MarketDisplayer.hpp"

#define NUMBER_OF_PAGES 4

// enum to identify the type of action that should be done when an option is selected within the market
// DISPLAY = keep displaying market, CLOSE_MARKET = close the market, QUIT_GAME = quit the game
enum marketAction {DISPLAY, CLOSE_MARKET, QUIT_GAME};

class MarketManager{
protected:

    // lists of market items
    RefillList refills;
    WeaponItemList weapons;
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
    void unlockSkin(char code); // called by purchaseSkin to unlock a new skin

    // functions to purchase and award a weapon of a given code
    void purchaseWeapon(char code);
    void activateWeapon(char code); //called by purchaseWeapon if weapon is already unlocked
    void unlockWeapon(char code); // called by purchaseWeapon to unlock a new weapon

    // functions to execute the user choice (when user presses ENTER), depending on the page the choice was made in
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

    // displayer for the market
    MarketDisplayer displayer;

    // returns the drawing of the skin of the specified code
    wstring getSkin(char code);

    // returns the weapon associated to the specified code
    pWeapon getWeapon(char code);

    // unlock all weapons whose codes appear in codeStr
    void addUnlockedWeapons(string codeStr);
    // unlock all skins whose codes appear in codeStr
    void addUnlockedSkins(string codeStr);

    // function to open the market in window win, starting from (start_x, start_y)
    void openMarket(WINDOW* win, int start_y, int start_x);

    // execute a generic input choice (change selection option, select option, ...) and returns a marketAction
    // indicating what should be done next (see above for explanation of marketAction enum meaning)
    marketAction executeInput(int choice);
};

typedef MarketManager* pMarketManager;

#endif //SUPERALFABROS_MARKETMANAGER_HPP