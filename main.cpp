#include "Lists/DynamicLevelList.hpp"
#include "Market/MarketManager.hpp"
#include <chrono>
#include "Utilities/Movement.hpp"
#include <cmath>
#include <unistd.h>
#include "Objects/AllObjects.hpp"
#include "Objects/Weapons/AllWeapons.hpp"
#include "Utilities/StringUtilities.h"

#include <string>

using namespace std;

#define TEMPO 500
#define MINTEMPO 40.0
#define vertical_shift  4
inline double CurrentTime_milliseconds() {
    return chrono::duration_cast<std::chrono::milliseconds>
            (chrono::high_resolution_clock::now().time_since_epoch()).count();
}


void move(pPlayer player, char choice, pDynamicLevelList levels, bool hasLanded, WINDOW *win) {
    pMap Map = levels->currentMap();
    static unsigned long long ncicli = 0;
    static Movement jumper = Movement(player);
    if (hasLanded) {
        jumper.set_endJump();
        ++ncicli;
    }
    switch (choice) {
        case 'w': // jump where and if possible, maximum of 4
            jumper.jump(win, Map, levels);
            break;
        case 's': // move player backward
            jumper.update_dx(0);
            break;
        case 'a': // move player leftward
            levels->movePlayer(win, player->x - 1, player->y);
            jumper.update_dx(-1);
            ncicli = 0;
            break;
        case 'd': // move player rightward
            levels->movePlayer(win, player->x + 1, player->y);
            jumper.update_dx(1);
            ncicli = 0;
            break;
        case 'q': // use weapon to left
            player->useWeaponLeft(win);
            levels->currentMap()->shootBullet(win, player->getWeapon()->x - 1, player->getWeapon()->y, 'l');
            break;
        case 'e': // use weapon to right
            player->useWeaponRight(win);
            levels->currentMap()->shootBullet(win, player->getWeapon()->x + 1, player->getWeapon()->y, 'r');
            break;
        case -1:
            if (ncicli > 1000000 && !jumper.is_onJump()) {
                jumper.update_dx(0);
                ncicli = 0;
            }
    }
}

void drawHeader(WINDOW *win, ProgressManager *progressManager, pPlayer player) {
    // format and print LIFE and ARMOUR strings
    wstring lifeStr = playerStatusFormatter(L"LIFE   > ", 13, player->getLife(), 10);
    wstring armourStr = playerStatusFormatter(L"ARMOUR > ", 13, player->getArmour(), 5);
    mvwaddwstr(win, start_y + 1, start_x + 1, lifeStr.c_str());
    mvwaddwstr(win, start_y + 2, start_x + 1, armourStr.c_str());

    // format and print MONEY and POINTS strings
    wstring money = L"MONEY  > ";
    wstring points = L"POINTS > ";
    progressFormatter(money, points, progressManager->getMoney(), progressManager->getPoints());
    mvwaddwstr(win, start_y + 1, width - 1 - money.length(), money.c_str());
    mvwaddwstr(win, start_y + 2, width - 1 - points.length(), points.c_str());
}

// call this function when market needs to be opened
// the function returns when the user decides to exit the market
// the function returns false if the user decides to quit the game within the market; false otherwise
bool moveToMarket(WINDOW* win, MarketManager* marketManager){
    nodelay(stdscr, FALSE);
    nodelay(win, FALSE);
    marketManager->openMarket(win, 5, 5);

    marketAction nextAction = DISPLAY;
    while (nextAction == DISPLAY) { //remain in market until closing or quitting is selected
        marketManager->displayer.initializeDisplay(); //pass data to menu displayer
        marketManager->displayer.display(); //display menu
        int choice = wgetch(win);
        nextAction = marketManager->executeInput(choice);
    }

    nodelay(stdscr, TRUE);
    nodelay(win, TRUE);
    return(nextAction != QUIT_GAME);
}

int main() {
    // seed the random number generator
    srand(time(nullptr));

    // create progress manager instance and load saved data
    pProgressManager progressManager = new ProgressManager("PlayerData.txt", "WeaponData.txt", "SkinData.txt");
    progressManager->loadSavedData();

    //const int vertical_shift = 4;
    // create a new player instance
    pPlayer player = new Player(1, 1, 100, vertical_shift);

    // create market manager instance and unlock purchased items
    MarketManager *marketManager = new MarketManager(player, progressManager);
    marketManager->addUnlockedSkins(progressManager->getUnlockedSkinsString());
    marketManager->addUnlockedWeapons(progressManager->getUnlockedWeaponsString());

    // load player saved armour, skin and weapon
    int savedArmour = progressManager->getSavedArmour();
    player->incrementArmour(savedArmour);
    char skinCode = progressManager->getCurrentSkinCode();
    player->changeSkin(marketManager->getSkin(skinCode));
    char weaponCode = progressManager->getCurrentWeaponCode();
    player->setWeapon(marketManager->getWeapon(weaponCode));

    string mapsFolder = "../maps/";
    // create the levels dynamic lists
    pDynamicLevelList levels = new DynamicLevelList(progressManager, player, mapsFolder);

    // initiate screen with ncurses
    initscr();
    cbreak();
    noecho(); //don't print the keys pressed while playing
    // set locale so that special chars will be recognized
    setlocale(LC_ALL, "");


    double delay = TEMPO;  //delay as gravity

    // hide the blinking cursor
    curs_set(0);

    addwstr(L"\n\n"
            " ███████╗██╗   ██╗██████╗ ███████╗██████╗      █████╗ ██╗     ███████╗ █████╗     ██████╗ ██████╗  ██████╗ ███████╗\n"
            " ██╔════╝██║   ██║██╔══██╗██╔════╝██╔══██╗    ██╔══██╗██║     ██╔════╝██╔══██╗    ██╔══██╗██╔══██╗██╔═══██╗██╔════╝\n"
            " ███████╗██║   ██║██████╔╝█████╗  ██████╔╝    ███████║██║     █████╗  ███████║    ██████╔╝██████╔╝██║   ██║███████╗\n"
            " ╚════██║██║   ██║██╔═══╝ ██╔══╝  ██╔══██╗    ██╔══██║██║     ██╔══╝  ██╔══██║    ██╔══██╗██╔══██╗██║   ██║╚════██║\n"
            " ███████║╚██████╔╝██║     ███████╗██║  ██║    ██║  ██║███████╗██║     ██║  ██║    ██████╔╝██║  ██║╚██████╔╝███████║\n"
            " ╚══════╝ ╚═════╝ ╚═╝     ╚══════╝╚═╝  ╚═╝    ╚═╝  ╚═╝╚══════╝╚═╝     ╚═╝  ╚═╝    ╚═════╝ ╚═╝  ╚═╝ ╚═════╝ ╚══════╝\n"
            "                                                                                                                  \n");
    refresh();
    getch();
    clear();


    //creating the window
    WINDOW *win = newwin(height + vertical_shift, width, start_y, start_x);
    refresh();

    // enable function keys
    keypad(win, true);

    // set to false if user decides to quit in the market menu
    bool keepPlaying = moveToMarket(win, marketManager);

    if(keepPlaying){
        // clear the window
        wclear(win);
        // draw the base map, then all the objects and then the player
        levels->currentMap()->drawBaseMap(win, vertical_shift);
        levels->currentMap()->drawObjects(win, vertical_shift);
        player->drawPlayer(win, vertical_shift);

        drawHeader(win, progressManager, player);
    }

    // refresh the window with the new data drawn
    wrefresh(win);
    noecho(); //don't print the keys pressed while playing
    nodelay(stdscr, TRUE); //make getch not wait for the input
    nodelay(win, TRUE); //make getch not wait for the input

    int lastx, lasty, lastlife, lastmoney, lastpoints;
    bool hasLanded = false;
    pMap lastMap;
    // detect player moves
    int choice = 0;

    auto frame = CurrentTime_milliseconds();
    auto start = frame;
    double appTime = 0;

    while (choice != 27 && player->getLife() > 0 && keepPlaying){
        lastlife = player->getLife();
        lastmoney = progressManager->getMoney();
        lastpoints = progressManager->getPoints();
        lastx = player->x;
        lasty = player->y;
        lastMap = levels->currentMap();

        // get choice from keyboard

        choice = wgetch(win);
        move(player, choice, levels, hasLanded, win);

        if ((CurrentTime_milliseconds() - start) > delay) // gravity, acts based on time passed
        {
            levels->movePlayer(win, player->x, player->y + 1); // fall
            hasLanded = lasty == player->y;
            start = CurrentTime_milliseconds();
            if (lasty != player->y) {
                delay = max(delay * 0.75, MINTEMPO);  // fall faster next time, delay is lower
            } else delay = TEMPO; // reset delay if not falling, no speed
        }

        // move the objects every second
        if ((CurrentTime_milliseconds() - appTime) > 1000) // every second
        {
            appTime = CurrentTime_milliseconds();

            levels->currentMap()->moveObjects(win, 0); // move all the objects
        }
        if(lastlife!=player->getLife()||lastmoney!=progressManager->getMoney()||lastpoints!= progressManager->getPoints()){
            wmove(win,start_y + 1, start_x + 1);
            wclrtoeol(win);
            wmove(win,start_y + 2, start_x + 1);
            wclrtoeol(win);
            drawHeader(win, progressManager, player);
        }


        if (levels->currentMap() != lastMap) { // if map changes, display market
                keepPlaying = moveToMarket(win, marketManager);
                wclear(win);
                drawHeader(win, progressManager, player);
            }

        // clear the window and draw Map and Objects
        wmove(win,start_y + vertical_shift, start_x );
        wclrtobot(win);
        levels->currentMap()->drawBaseMap(win, vertical_shift);
        levels->currentMap()->drawObjects(win, vertical_shift);
        player->drawPlayer(win, vertical_shift);
        // refresh the window
        wrefresh(win);
    }
    nodelay(stdscr, FALSE);

    progressManager->updateArmour(player->getArmour());
    progressManager->saveProgress();

    wclear(win);
    wrefresh(win);
    addwstr(L"\n\n"
            "    ▄██████▄     ▄████████    ▄▄▄▄███▄▄▄▄      ▄████████       ▄██████▄   ▄█    █▄     ▄████████    ▄████████ \n"
            "   ███    ███   ███    ███  ▄██▀▀▀███▀▀▀██▄   ███    ███      ███    ███ ███    ███   ███    ███   ███    ███ \n"
            "   ███    █▀    ███    ███  ███   ███   ███   ███    █▀       ███    ███ ███    ███   ███    █▀    ███    ███ \n"
            "  ▄███          ███    ███  ███   ███   ███  ▄███▄▄▄          ███    ███ ███    ███  ▄███▄▄▄      ▄███▄▄▄▄██▀ \n"
            " ▀▀███ ████▄  ▀███████████  ███   ███   ███ ▀▀███▀▀▀          ███    ███ ███    ███ ▀▀███▀▀▀     ▀▀███▀▀▀▀▀   \n"
            "   ███    ███   ███    ███  ███   ███   ███   ███    █▄       ███    ███ ███    ███   ███    █▄  ▀███████████ \n"
            "   ███    ███   ███    ███  ███   ███   ███   ███    ███      ███    ███ ███    ███   ███    ███   ███    ███ \n"
            "   ████████▀    ███    █▀    ▀█   ███   █▀    ██████████       ▀██████▀   ▀██████▀    ██████████   ███    ███ \n"
            "                                                                                                   ███    ███ \n");

    refresh();
    getch();

    endwin();
    return 0;
}