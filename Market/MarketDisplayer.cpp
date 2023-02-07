//
// Created by vboxuser on 26.01.23.
//

#include "MarketDisplayer.hpp"

wstring MarketDisplayer::getMoneyString() {
    return(L"MONEY > " + to_wstring(progressManager->getMoney()));
}

void MarketDisplayer::initializeMainPage() {
    wstring title = L"███    ███  █████  ██████  ██   ██ ███████ ████████ \n"
                    "████  ████ ██   ██ ██   ██ ██  ██  ██         ██    \n"
                    "██ ████ ██ ███████ ██████  █████   █████      ██    \n"
                    "██  ██  ██ ██   ██ ██   ██ ██  ██  ██         ██    \n"
                    "██      ██ ██   ██ ██   ██ ██   ██ ███████    ██    \n";

    const int topRowsCount = 0;
    wstring topRows[topRowsCount] = {};

    const int optCount = 3;
    wstring options[optCount] = {L"REFILLS", L"WEAPONS", L"SKINS"};

    const int closingOptCount = 2;
    wstring closingOptions[closingOptCount] = {L"RESUME GAME", L"QUIT GAME"};

    MenuDisplayer::initTopPart(title, topRows, topRowsCount);
    MenuDisplayer::initOptions(options, optCount, closingOptions, closingOptCount);
}

void MarketDisplayer::initializeRefillPage() {
    wstring title = L"██████  ███████ ███████ ██ ██      ██      ███████ \n"
                    "██   ██ ██      ██      ██ ██      ██      ██      \n"
                    "██████  █████   █████   ██ ██      ██      ███████ \n"
                    "██   ██ ██      ██      ██ ██      ██           ██ \n"
                    "██   ██ ███████ ██      ██ ███████ ███████ ███████ \n";

    const int topRowsCount = 3;
    wstring money = getMoneyString();
    wstring playerStatus = L"LIFE > " + to_wstring(player->getLife()) + L"\t\tARMOUR > " + to_wstring(player->getArmour());
    wstring label = L"REFILL\t\tAMOUNT\t\tPRICE";
    wstring topRows[topRowsCount] = {money, playerStatus, label};

    const int optCount = this->refills->getCount();
    wstring options[optCount];
    this->refills->getRefillInfoStrings(options, optCount);

    const int closingOptCount = 1;
    wstring closingOptions[closingOptCount] = {L"BACK"};

    MenuDisplayer::initTopPart(title, topRows, topRowsCount);
    MenuDisplayer::initOptions(options, optCount, closingOptions, closingOptCount);
}

void MarketDisplayer::initializeWeaponPage() {
    wstring title = L"██     ██ ███████  █████  ██████   ██████  ███    ██ ███████ \n"
                    "██     ██ ██      ██   ██ ██   ██ ██    ██ ████   ██ ██      \n"
                    "██  █  ██ █████   ███████ ██████  ██    ██ ██ ██  ██ ███████ \n"
                    "██ ███ ██ ██      ██   ██ ██      ██    ██ ██  ██ ██      ██ \n"
                    " ███ ███  ███████ ██   ██ ██       ██████  ██   ████ ███████\n";

    const int topRowsCount = 2;
    wstring money = getMoneyString();
    wstring label = L"WEAPON\t\tRANGE\t\tDAMAGE\t\tPRICE";
    wstring topRows[topRowsCount] = {money, label};

    const int optCount = this->weapons->getCount();
    wstring options[optCount];
    this->weapons->getWeaponInfoString(options, optCount, progressManager->getCurrentWeaponCode());

    const int closingOptCount = 1;
    wstring closingOptions[closingOptCount] = {L"BACK"};

    MenuDisplayer::initTopPart(title, topRows, topRowsCount);
    MenuDisplayer::initOptions(options, optCount, closingOptions, closingOptCount);
}

void MarketDisplayer::initializeSkinPage() {
    wstring title = L"███████ ██   ██ ██ ███    ██ ███████ \n"
                    "██      ██  ██  ██ ████   ██ ██      \n"
                    "███████ █████   ██ ██ ██  ██ ███████ \n"
                    "     ██ ██  ██  ██ ██  ██ ██      ██ \n"
                    "███████ ██   ██ ██ ██   ████ ███████ \n";

    const int topRowsCount = 2;
    wstring money = getMoneyString();
    wstring label = L"SKIN\tNAME\t\tPRICE";
    wstring topRows[topRowsCount] = {money, label};

    const int optCount = this->skins->getCount();
    wstring options[optCount];
    this->skins->getSkinInfoStrings(options, optCount, progressManager->getCurrentSkinCode());

    const int closingOptCount = 1;
    wstring closingOptions[closingOptCount] = {L"BACK"};

    MenuDisplayer::initTopPart(title, topRows, topRowsCount);
    MenuDisplayer::initOptions(options, optCount, closingOptions, closingOptCount);
}

//PUBLIC
void MarketDisplayer::initGameReferences(Player* player, ProgressManager* progressManager){
    this->player = player;
    this->progressManager = progressManager;
}

void MarketDisplayer::initMarketContent(RefillList* refills, WeaponList* weapons, SkinList* skins){
    this->refills = refills;
    this->weapons = weapons;
    this->skins = skins;
}

void MarketDisplayer::initializeDisplay(){
    switch(this->openPage){
        case 0:
            initializeMainPage();
            break;
        case 1:
            initializeRefillPage();
            break;
        case 2:
            initializeWeaponPage();
            break;
        case 3:
            initializeSkinPage();
            break;
        default:
            break;
    }
}

int MarketDisplayer::getPage() {
    return(this->openPage);
}

void MarketDisplayer::changePage(int newPage) {
    this->openPage = newPage;
    this->highlight = 0;
}