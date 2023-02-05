#include "Lists/DynamicLevelList.hpp"
#include <chrono>
#include "Movement.hpp"


#define TEMPO 500
#define MINTEMPO 40.0

inline double CurrentTime_milliseconds() {
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

    noecho(); //don't print the keys pressed while playing
    nodelay(win, TRUE); //make getch not wait for the input


    int lastx, lasty;
    bool hasLanded = false;
    pMap lastMap;
    // detect player moves
    int choice;
    /*int maxh = height;
    //int dx = 0;
    //int dy = 1;*/

    auto frame = CurrentTime_milliseconds();
    auto start = frame;

    //int choice_old = 's';
    do {
        //if (CurrentTime_milliseconds() - frame > 20) {
        printf("aa");
        lastx = player->x;
        lasty = player->y;
        lastMap = levels->currentMap();

        // get choice from keyboard
        choice = wgetch(win);
        move(player, choice, levels, hasLanded);

        if ((CurrentTime_milliseconds() - start) > delay) // gravity, acts based on time passed
        {
            levels->movePlayer(player->x, player->y + 1); // fall
            hasLanded = lasty == player->y;
            start = CurrentTime_milliseconds();
            if (lasty != player->y) {
                delay = max(delay * 0.75, MINTEMPO);  // fall faster next time, delay is lower delay/(delay+10.0);
            } else delay = TEMPO; // reset delay if not falling, no speed
        }


        if (lastx != player->x || lasty != player->y || levels->currentMap() != lastMap) { // if something changes

            if (levels->currentMap() != lastMap) // if map changes
            {
                // clear the window and draw Map and Objects
                wclear(win);
                levels->currentMap()->drawBaseMap(win);
                levels->currentMap()->drawObjects(win);
            }
            mvwaddwstr(win, lasty, lastx, L" "); // clear previous coordinate where player was
            player->drawPlayer(win);
            // refresh the window
            wrefresh(win);
        }
    } while (choice != 'q' && player->getLife()> 0);
    nodelay(stdscr,FALSE);

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