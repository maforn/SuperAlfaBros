//
// Created by matteo on 23/11/2022.
//
#include "Lists/DynamicLevelList.hpp"

int main() {
    // create a new player instance
    pPlayer player = new Player(1, 1, 100);
    string mapsFolder = "../maps/";
    // create the levels dynamic lists
    pDynamicLevelList levels = new DynamicLevelList(player, mapsFolder);

    // initiate screen with ncurses
    initscr();
    // set locale so that special chars will be recognized
    setlocale(LC_ALL, "");
    // parameters for window
    int height, width, start_y, start_x;
    height = 30;
    width = 90;
    start_y = 0;
    start_x = 0;

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
    WINDOW *win = newwin(height, width, start_y, start_x);
    refresh();

    // clear the window
    wclear(win);
    // draw the base map, then all the objects and then the player
    levels->currentMap()->drawBaseMap(win);
    levels->currentMap()->drawObjects(win);
    player->drawPlayer(win);
    // refresh the window with the new data drawn
    wrefresh(win);

    // detect player moves
    int choice;
    do {
        // get choice from keyboard
        choice = wgetch(win);
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
        }
        // clear the windows and draw everything again
        wclear(win);
        if (player->getLife() <= 0) {
            break;
        }
        levels->currentMap()->drawBaseMap(win);
        levels->currentMap()->drawObjects(win);
        player->drawPlayer(win);
        // refresh the window
        wrefresh(win);
    } while (choice != KEY_EXIT);
    wrefresh(win);
    addwstr(L"\n\n    ▄██████▄     ▄████████    ▄▄▄▄███▄▄▄▄      ▄████████       ▄██████▄   ▄█    █▄     ▄████████    ▄████████ \n"
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