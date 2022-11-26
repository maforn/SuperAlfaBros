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

    initscr();
    setlocale(LC_ALL, "");
    // parameters for window
    int height, width, start_y, start_x;
    height = 30;
    width = 90;
    start_y = 0;
    start_x = 0;

    //creating the window
    WINDOW *win = newwin(height, width, start_y, start_x);
    refresh();

    curs_set(0); // HIDE CURSOR

    wclear(win);
    levels->currentMap()->drawBaseMap(win);
    levels->currentMap()->drawObjects(win);
    player->drawPlayer(win);
    wrefresh(win);
    int choice;
    do {
        choice = wgetch(win);
        switch (choice) {
            case 'w':
                levels->currentMap()->movePlayer(player->x, player->y - 1);
                break;
            case 's':
                levels->currentMap()->movePlayer(player->x, player->y + 1);
                break;
            case 'a':
                levels->currentMap()->movePlayer(player->x - 1, player->y);
                break;
            case 'd':
                levels->currentMap()->movePlayer(player->x + 1, player->y);
                break;
        }
        wclear(win);
        levels->currentMap()->drawBaseMap(win);
        levels->currentMap()->drawObjects(win);
        player->drawPlayer(win);
        wrefresh(win);
    } while (choice != KEY_EXIT);
    getch();
    endwin();

    return 0;
}