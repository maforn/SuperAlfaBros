//
// Created by vboxuser on 26.01.23.
//

#ifndef SUPERALFABROS_MARKETDISPLAYER_HPP
#define SUPERALFABROS_MARKETDISPLAYER_HPP

#include "MenuDisplayer.hpp"
#include "RefillList.hpp"
#include "WeaponList.hpp"
#include "SkinList.hpp"
#include "../Progress/ProgressManager.hpp"
#include "../Objects/Player.hpp"

class MarketDisplayer :public MenuDisplayer{
protected:

    // pointer to the Player object
    Player* player;
    // pointer to the ProgressManager objects
    ProgressManager* progressManager;
    // pointer to the market's RefillList object
    RefillList* refills;
    // pointer to the market's WeaponList object
    WeaponList* weapons;
    // pointer to the market's SkinList object
    SkinList* skins;

    // identifies the currently open page:
    // 0)main page  1)refills page  2)weapons page  3)skins page
    int openPage;

    // returns a string in the format "MONEY > (current amount of money)"
    wstring getMoneyString();

    // functions that initialize the content of the menu. One for each page.
    void initializeMainPage();
    void initializeRefillPage();
    void initializeSkinPage();
    void initializeWeaponPage();

public:

    // initializes references to Player and ProgressManager objects
    void initGameReferences(Player* player, ProgressManager* progressManager);

    // initializes references to market's RefillList, WeaponList and SkinList objects
    void initMarketContent(RefillList* refills, WeaponList* weapons, SkinList* skins);

    // initializes the content of the menu depending on the currently open page
    void initializeDisplay();

    // returns the number representing the currently open page (openPage)
    int getPage();

    // changes openPage value to newPage. Used before initializing display
    void changePage(int newPage);
};

#endif //SUPERALFABROS_MARKETDISPLAYER_HPP
