//
// Created by vboxuser on 04/02/23.
//

#include "Movement.hpp"
#include "Lists/DynamicLevelList.hpp"
#include <string.h>

/*void show_title() {
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
}

void show_endscreen(WINDOW *win) {
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
}*/

class jumping {
protected:
    int dx;
    int maxh;
    pObject dummy;
    pPlayer player;
    bool onJump;
    int nJumps;
public:
    jumping(pPlayer player) {
        this->dx = 0;
        this->maxh = height;
        this->player = player;
        this->onJump = false;
        this->nJumps = 0;
    }

    void jump(pMap Map, pDynamicLevelList levels) {
        if (Map->detectCollision(player->x, player->y - 1, dummy) != 'W') {
            if (Map->detectCollision(player->x, player->y + 1, dummy) != ' ' && !this->onJump) {
                this->onJump = true;
                this->maxh = player->y - 4;
                levels->movePlayer(player->x + dx, player->y - 1);
                levels->movePlayer(player->x + dx, player->y - 1);
                /*//dy=-1;
                // if within bounds
                //if (choice_old == 'd') dx = 1;
                //else if (choice_old == 'a') dx = -1;
                if (player->y == lasty - 1 && lasty > 2)
                    levels->movePlayer(player->x, player->y -
                                                  1); // if previous successful and within bounds
                if (player->y == lasty - 2 && lasty > 3)
                    levels->movePlayer(player->x, player->y -
                                                  1); // if previous successful and within bounds
                //start = CurrentTime_milliseconds();*/
            } else if (player->y > maxh && this->nJumps < MAX_JUMPS) {
                levels->movePlayer(player->x + dx, player->y - 1);
                nJumps++;

            } else {
                maxh = height;
                this->onJump = false;
            }
            levels->movePlayer(player->x + dx, player->y);
        } else {
            maxh = height;
            this->onJump = false;
        }
    }

    void update_dx(int ndx) {
        this->dx = ndx;
    }

    bool is_onJump() {
        return this->onJump;
    }

    void set_endJump() {
        this->onJump = false;
    }
};


void move(pPlayer player, char choice, pDynamicLevelList levels, bool hasLanded) {
    pMap Map = levels->currentMap();
    static unsigned long long ncicli = 0;
    static jumping jumper = jumping(player);
    if (hasLanded) {
        jumper.set_endJump();
        ++ncicli;
    }
    switch (choice) {
        case 'w': // jump where and if possible, maximum of 4
            jumper.jump(Map, levels);
            break;
        case 's': // move player backward
            jumper.update_dx(0);
            break;
        case 'a': // move player leftward
            levels->movePlayer(player->x - 1, player->y);
            //choice_old = 'a';
            jumper.update_dx(-1);
            ncicli = 0;
            //dx = -1;
            //wcout<<"AAAAAAAAAAAAAA"<<endl;
            break;
        case 'd': // move player rightward
            levels->movePlayer(player->x + 1, player->y);
            jumper.update_dx(1);
            ncicli = 0;
            break;
        case -1:
            if (ncicli > 1000000 && !jumper.is_onJump()) {
                //wcout << "c" << endl;
                jumper.update_dx(0);
                ncicli = 0;
            }
    }
}

//void update_window()