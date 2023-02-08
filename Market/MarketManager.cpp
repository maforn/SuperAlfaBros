//
// Created by vboxuser on 23.01.23.
//


#include "MarketManager.hpp"

void MarketManager::initializeRefills(){
    refills.addRefill('L', L"Life", 10, 40);
    refills.addRefill('A', L"Armour",5, 25);
}

void MarketManager::initializeWeapons() {
    weapons.addWeapon(new Gun(), 50);
    weapons.addWeapon(new Revolver(), 50);
    weapons.addWeapon(new Shotgun(), 100);
    weapons.addWeapon(new Rifle(), 150);
    weapons.addWeapon(new Sniper(), 200);
}

void MarketManager::initializeSkins() {
    skins.addSkin('A', L"0", L"Default", 50);
    skins.addSkin('B', L"1", L"Noob", 50);
    skins.addSkin('C', L"2", L"Mid", 100);
    skins.addSkin('D', L"3", L"Expert", 150);
    skins.addSkin('E', L"4", L"Pro", 200);
}

void MarketManager::initializeDisplayer() {
    displayer.initGameReferences(this->player, this->progressManager);
    displayer.initMarketContent(&refills, &weapons, &skins);
}

void MarketManager::purchaseRefill(char code){
    int price = refills.getPrice(code);
    if(price != -1){
        int money = progressManager -> getMoney();
        if(price <= money){
            bool purchased = awardRefill(code);
            if(purchased)
                progressManager -> incrementMoney(-price);
        }
    }
}

bool MarketManager::awardRefill(char code){
    int amount = refills.getAmount(code);
    bool awarded = false;

    switch(code){
        case 'L':
            awarded = player->incrementLife(amount);
            break;
        case 'A':
            awarded = player->incrementArmour(amount);
            progressManager->updateArmour(player->getArmour());
            break;
        default:
            break;
    }
    return(awarded);
}

void MarketManager::purchaseWeapon(char code) {
    int price = weapons.getPrice(code);
    if(price == 0)
        activateWeapon(code);
    else if(price != -1 && price <= progressManager->getMoney())
        unlockWeapon(code, price);
}
void MarketManager::activateWeapon(char code) {
    progressManager->changeCurrentWeapon(code);
    pWeapon selectedWeapon = weapons.getWeapon(code);
    player->setWeapon(selectedWeapon);
}
void MarketManager::unlockWeapon(char code, int price) {
    weapons.removePrice(code);
    progressManager->unlockNewWeapon(code);
    progressManager->incrementMoney(-price);
}

void MarketManager::purchaseSkin(char code) {
    int price = skins.getPrice(code);
    if(price == 0)
        activateSkin(code);
    else if(price != -1 && price <= progressManager->getMoney())
        unlockSkin(code, price);
}
void MarketManager::activateSkin(char code) {
    player->changeSkin(skins.getDrawing(code));
    progressManager->changeCurrentSkin(code);
}
void MarketManager::unlockSkin(char code, int price) {
    skins.removePrice(code);
    progressManager->unlockNewSkin(code);
    progressManager->incrementMoney(-price);
}

void MarketManager::executeChoice(int choice) {
    int currentPage = displayer.getPage();
    switch(currentPage){
        case 0:
            executeMainPageChoice(choice); break;
        case 1:
            executeRefillPageChoice(choice); break;
        case 2:
            executeWeaponPageChoice(choice); break;
        case 3:
            executeSkinPageChoice(choice); break;
        default:
            break;
    }
}

void MarketManager::executeMainPageChoice(int choice) {
        int selectedPage = choice + 1;
        displayer.changePage(selectedPage);
}

void MarketManager::executeRefillPageChoice(int choice) {
    int refillCount = refills.getCount();
    if(choice < refillCount){
        char refillCode = refills.getCodeByIndex(choice);
        purchaseRefill(refillCode);
    }
    else if(choice == refillCount)
        back();
}

void MarketManager::executeWeaponPageChoice(int choice) {
    int weaponCount = weapons.getCount();
    if(choice < weaponCount){
        char weaponCode = weapons.getCodeByIndex(choice);
        purchaseWeapon(weaponCode);
    }
    else if(choice == weaponCount)
        back();
}

void MarketManager::executeSkinPageChoice(int choice) {
    int skinCount = skins.getCount();
    if(choice < skinCount){
        char skinCode = skins.getCodeByIndex(choice);
        purchaseSkin(skinCode);
    }
    else if(choice == skinCount)
        back();
}

void MarketManager::back() {
    displayer.changePage(0);
}

bool MarketManager::isExitChosen(int choice) {
    return(displayer.getPage() == 0 && choice == NUMBER_OF_PAGES - 1);
}

bool MarketManager::isQuitChosen(int choice){
    return(displayer.getPage() == 0 && choice == NUMBER_OF_PAGES);
}

//PUBLIC
MarketManager::MarketManager(Player* player, ProgressManager* progressManager){
    this -> player = player;
    this -> progressManager = progressManager;

    initializeRefills();
    initializeWeapons();
    initializeSkins();
    initializeDisplayer();
}

wstring MarketManager::getSkin(char code) {
    return skins.getDrawing(code);
}

pWeapon MarketManager::getWeapon(char code){
    return weapons.getWeapon(code);
}

void MarketManager::addUnlockedWeapons(string codeStr){
    for(int i = 0; i < codeStr.length(); i++)
        weapons.removePrice(codeStr[i]);
}

void MarketManager::addUnlockedSkins(string codeStr){
    for(int i = 0; i < codeStr.length(); i++)
        skins.removePrice(codeStr[i]);
}

void MarketManager::openMarket(WINDOW* win, int start_y, int start_x){
    //update items' prices to match difficulty level
    double difficulty = progressManager->getDifficulty();
    refills.multiplyPrices(difficulty);
    weapons.multiplyPrices(difficulty);

    displayer.changePage(0); //open first page
    displayer.initMenuWindow(win, start_y, start_x); //setup menu top left corner
}

marketAction MarketManager::executeInput(int input) {
    marketAction nextAction = DISPLAY;
    if(input != 10)
        displayer.changeOptions(input);
    else{
        int choice = displayer.getChoice();
        if(isExitChosen(choice))
            nextAction = CLOSE_MARKET;
        else if(isQuitChosen(choice))
            nextAction = QUIT_GAME;
        else
            executeChoice(choice);
    }
    return nextAction;
}