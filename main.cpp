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

inline double CurrentTime_milliseconds() {
    return chrono::duration_cast<std::chrono::milliseconds>
            (chrono::high_resolution_clock::now().time_since_epoch()).count();
}


void move(pPlayer player, char choice, pDynamicLevelList levels, bool hasLanded, WINDOW* win) {
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

void drawHeader(WINDOW* win, ProgressManager* progressManager, pPlayer player) {
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

int main() {
    // seed the random number generator
    srand(time(nullptr));

    // create progress manager instance and load saved data
    pProgressManager progressManager = new ProgressManager("PlayerData.txt", "WeaponData.txt", "SkinData.txt");
    progressManager->loadSavedData();

    int vertical_shift = 4;
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

    // clear the window
    wclear(win);
    // draw the base map, then all the objects and then the player
    levels->currentMap()->drawBaseMap(win, vertical_shift);
    levels->currentMap()->drawObjects(win, vertical_shift);
    player->drawPlayer(win, vertical_shift);

    drawHeader(win, progressManager, player);

    // refresh the window with the new data drawn
    wrefresh(win);
    noecho(); //don't print the keys pressed while playing
    nodelay(stdscr, TRUE); //make getch not wait for the input
    nodelay(win, TRUE); //make getch not wait for the input

    int lastx, lasty;
    bool hasLanded = false;
    pMap lastMap;
    // detect player moves
    int choice;

    auto frame = CurrentTime_milliseconds();
    auto start = frame;
    double appTime = 0;

    bool keepPlaying = true; // set to false if user decides to quit in the market menu
    do {
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
/*
        choice = getch();
        switch (choice) {
            case 'w': // move player forward
                levels->movePlayer(win, player->x, player->y - 1);
                break;
            case 's': // move player backward
                levels->movePlayer(win, player->x, player->y + 1);
                break;
            case 'a': // move player leftward
                levels->movePlayer(win, player->x - 1, player->y);
                break;
            case 'd': // move player rightward
                levels->movePlayer(win, player->x + 1, player->y);
                break;
            case 'q': // use weapon to left
                player->useWeaponLeft(win);
                levels->currentMap()->shootBullet(win, player->getWeapon()->x - 1, player->getWeapon()->y, 'l');

                break;
            case 'e': // use weapon to right
                player->useWeaponRight(win);
                levels->currentMap()->shootBullet(win, player->getWeapon()->x + 1, player->getWeapon()->y, 'r');
                break;
            case ' ': // jump where and if possible, maximum of 3
                if(lasty > 1) levels->movePlayer(win,player->x, player->y-1);   // if within bounds
                if(player->y==lasty-1 && lasty > 2) levels->movePlayer(win,player->x, player->y-1); // if previous successful and within bounds
                if(player->y==lasty-2 && lasty > 3) levels->movePlayer(win,player->x, player->y-1); // if previous successful and within bounds
                delay = TEMPO;
                break;
            default:
                break;
        }





         if ((CurrentTime_milliseconds() - start)>delay) // gravity, acts based on time passed
        {
            levels->movePlayer(win,player->x, player->y + 1); // fall */

            start = CurrentTime_milliseconds();
            if (lasty != player->y) {
                delay = max(delay * 0.75, MINTEMPO);  // fall faster next time, delay is lower
            } else delay = TEMPO; // reset delay if not falling, no speed
        }

        // move the objects every second
        if ((CurrentTime_milliseconds() - appTime )> 1000) // every second
        {

            appTime = CurrentTime_milliseconds();

            levels->currentMap()->moveObjects(win, 0); // move all the objects
            wclear(win);
            drawHeader(win, progressManager, player);
            levels->currentMap()->drawBaseMap(win, vertical_shift);
            levels->currentMap()->drawObjects(win, vertical_shift);
            player->drawPlayer(win, vertical_shift);
            wrefresh(win);
        }


        if (lastx != player->x || lasty != player->y || levels->currentMap() != lastMap) { // if something changes

            if (levels->currentMap() != lastMap){ // if map changes, display market
                nodelay(stdscr, FALSE);
                nodelay(win, FALSE);
                marketManager->openMarket(win, 5, 5);

                marketAction nextAction = DISPLAY;
                while(nextAction == DISPLAY){
                    marketManager->displayer.initializeDisplay(); //pass data to menu
                    marketManager->displayer.display(); //display menu structure (not options)
                    choice = wgetch(win);
                    nextAction = marketManager->executeInput(choice);
                }

                nodelay(stdscr, TRUE);
                nodelay(win, TRUE);
                keepPlaying = nextAction != QUIT_GAME;
            }

            // clear the window and draw Map and Objects
            wclear(win);
            drawHeader(win, progressManager, player);
            levels->currentMap()->drawBaseMap(win, vertical_shift);
            levels->currentMap()->drawObjects(win, vertical_shift);

            //clearXY(win, lastx, lasty); // clear previous coordinate where player was
            player->drawPlayer(win, vertical_shift);

            // refresh the window
            wrefresh(win);
        }
    } while (choice != 27 && player->getLife() > 0 && keepPlaying);
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