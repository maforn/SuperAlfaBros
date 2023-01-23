#include "Lists/DynamicLevelList.hpp"
#include <chrono>
#include <cmath>
#include <unistd.h>
#include <thread>

static bool isRunning = true;

void work(WINDOW*win, pDynamicLevelList levels){
    using namespace std::literals::chrono_literals;
    while (isRunning){
        levels->currentMap()->moveObjects(win); // move all the objects
        wrefresh(win);
        std::this_thread::sleep_for(std::chrono::milliseconds(500));

    }
}

inline double CurrentTime_milliseconds()
{
    return chrono::duration_cast<std::chrono::milliseconds>
            (chrono::high_resolution_clock::now().time_since_epoch()).count();
}



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

    cbreak();
    noecho(); //don't print the keys pressed while playing
    nodelay(stdscr, TRUE); //make getch not wait for the input
    nodelay(win, TRUE); //make getch not wait for the input

    int lastx, lasty;
    pMap lastMap;
    // detect player moves
    int choice;

    auto start = CurrentTime_milliseconds();
    thread th(work, win, levels);
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
            /*case ' ': // jump where and if possible, maximum of 3
                if(lasty > 1) levels->movePlayer(player->x, player->y-1);   // if within bounds
                if(player->y==lasty-1 && lasty > 2) levels->movePlayer(player->x, player->y-1); // if previous successful and within bounds
                if(player->y==lasty-2 && lasty > 3) levels->movePlayer(player->x, player->y-1); // if previous successful and within bounds
                delay = TEMPO;
                break;*/
        }

        /*
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
         */


        if (lastx!=player->x || lasty!=player->y || levels->currentMap()!=lastMap) { // if something changes
            if (levels->currentMap()!=lastMap) // if map changes
            {
                // clear the window and draw Map and Objects
                isRunning = false;
                th.join();
                wclear(win);
                levels->currentMap()->drawBaseMap(win);
                levels->currentMap()->drawObjects(win);
                isRunning = true;
                thread th(work, win, levels);
            }
            mvwaddwstr(win, lasty, lastx, L" "); // clear previous coordinate where player was
            player->drawPlayer(win);
            // refresh the window
            wrefresh(win);
        }

    } while (choice != 'q' && player->getLife()>0);
    isRunning = false;
    th.join();
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