#include "Lists/DynamicLevelList.hpp"
#include "Market/MarketManager.hpp"
#include "Progress/ProgressManager.hpp"
#include <chrono>
#include <cmath>
#include "Utilities/StringUtilities.h"

#include <string>
using namespace std;

inline double CurrentTime_milliseconds()
{
    return chrono::duration_cast<std::chrono::milliseconds>
            (chrono::high_resolution_clock::now().time_since_epoch()).count();
}

int main() {
    // create progress manager instance and load saved data
    ProgressManager* progressManager = new ProgressManager("PlayerData.txt", "WeaponData.txt", "SkinData.txt");
    progressManager->loadSavedData();
    progressManager->incrementMoney(800);

    // create a new player instance
    pPlayer player = new Player(1, 1, 20);

    // create market manager instance and unlock purchased items
    MarketManager* marketManager = new MarketManager(player, progressManager);
    marketManager->addUnlockedSkins(progressManager->getUnlockedSkinsString());
    marketManager->addUnlockedWeapons(progressManager->getUnlockedWeaponsString());

    // load player saved armour, skin and weapon
    int savedArmour = progressManager->getSavedArmour();
    player->incrementArmour(savedArmour);
    char skinCode = progressManager->getCurrentSkinCode();
    player->changeSkin(marketManager->getSkin(skinCode));
    char weaponCode = progressManager->getCurrentWeaponCode();
    player->changeDamage(marketManager->getWeaponDamage(weaponCode));

    string mapsFolder = "../maps/";
    // create the levels dynamic lists
    pDynamicLevelList levels = new DynamicLevelList(player, mapsFolder);

    // initiate screen with ncurses
    initscr();
    cbreak();
    noecho(); //don't print the keys pressed while playing
    // set locale so that special chars will be recognized
    setlocale(LC_ALL, "");

    // parameters for window
    int height, width, vertical_shift, start_y, start_x;
    height = 30;
    width = 90;
    vertical_shift = 4;
    start_y = 0;
    start_x = 0;

    const double TEMPO = 500;
    const double MINTEMPO = 40.0;
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

    // refresh the window with the new data drawn
    wrefresh(win);
    getch();

    // display market
    wclear(win);
    marketManager->openMarket(win, 5, 5);
    bool quitGame = marketManager->waitForMarketClosure();
    wclear(win);
    wrefresh(win);

    nodelay(stdscr, TRUE); //make getch not wait for the input


    int lastx, lasty;
    pMap lastMap;
    // detect player moves
    int choice;

    auto start = CurrentTime_milliseconds();

    do {
        lastx = player->x;
        lasty = player->y;
        lastMap = levels->currentMap();
        // get choice from keyboard
        choice = getch();
        switch (choice) {
            case 'w': // move player forward
                levels->movePlayer(player->x, player->y - 1);
                break;
            case 's': // move player backward
                levels->movePlayer(player->x, player->y + 1);
                break;
            case 'a': // move player leftward
                levels->movePlayer(player->x - 1, player->y);
                break;
            case 'd': // move player rightward
                levels->movePlayer(player->x + 1, player->y);
                break;
            case ' ': // jump where and if possible, maximum of 3
                if(lasty > 1) levels->movePlayer(player->x, player->y-1);   // if within bounds
                if(player->y==lasty-1 && lasty > 2) levels->movePlayer(player->x, player->y-1); // if previous successful and within bounds
                if(player->y==lasty-2 && lasty > 3) levels->movePlayer(player->x, player->y-1); // if previous successful and within bounds
                delay = TEMPO;
                break;
        }

        if ((CurrentTime_milliseconds() - start)>delay) // gravity, acts based on time passed
        {
            levels->movePlayer(player->x, player->y + 1); // fall
            start = CurrentTime_milliseconds();
            if (lasty!=player->y)
            {
                delay = max(delay*0.75,MINTEMPO);  // fall faster next time, delay is lower delay/(delay+10.0);
            }
            else delay = TEMPO; // reset delay if not falling, no speed
        }


        if (lastx!=player->x || lasty!=player->y || levels->currentMap()!=lastMap) { // if something changes

            if (levels->currentMap()!=lastMap) // if map changes
            {
                // clear the window and draw Map and Objects
                wclear(win);
                levels->currentMap()->drawBaseMap(win,vertical_shift);
                levels->currentMap()->drawObjects(win,vertical_shift);
            }
            mvwaddwstr(win, lasty, lastx, L" "); // clear previous coordinate where player was
            player->drawPlayer(win,vertical_shift);
            // refresh the window
            wrefresh(win);
        }
    } while (choice != 'q' && player->getLife()>0);
    nodelay(stdscr, FALSE);

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