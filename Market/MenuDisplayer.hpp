//
// Created by vboxuser on 24.01.23.
//

#ifndef SUPERALFABROS_MENUDISPLAYER_HPP
#define SUPERALFABROS_MENUDISPLAYER_HPP

#include "../Utilities/StringUtilities.h"
#include <ncurses.h>
#include <string>
using namespace std;

#define MAX_TOP_ROWS 5 // max number of topRows
#define MAX_OPTIONS 10 // max number of options
#define MAX_CLOSING 5 // max number of closingOptions
#define VERTICAL_SPACING 2 // vertical spacing between different parts of menu

class MenuDisplayer{
protected:

    // pointer to the open window
    WINDOW *win;
    // coordinates of window sarting point (ie window top-left corner)
    int menuStartY, menuStartX;

    // title string
    wstring title;

    // strings that will be printed at the top of the menu, right below the title
    wstring topRows[MAX_TOP_ROWS];
    int topRowsCount{};

    // strings representing the options available to the user in the menu. Printed in the middle of the menu
    wstring options[MAX_OPTIONS];
    int optionsCount{};

    // string representing options the user can select in orderr to navigate the menu. Printed at the bottom of the menu
    wstring closingOptions[MAX_CLOSING];
    int closingOptCount{};

    // used to keep track of the last line where something was printed
    int lastY;

    // index of the currently highlighted option
    int highlight;

    // initializes the variables associated to the top part of the menu, ie title and topRows
    void initTopPart(wstring title, wstring topRows[], int topRowsCount);

    // initializes all options: options and closingOptions
    void initOptions(wstring options[], int optionsCount, wstring closingOpt[], int closingOptCount);

    // prints the title in the menu
    void printTitle();

    // draws the top part of the menu, ie title and topRows
    void drawTopPart();

    // draws both options and closing options
    void drawAllOptions();

    // draws the options starting from (startX, startY) and shifting downwards by verticalShift after every option.
    void drawOptions(int startY, int startX, int verticalShift);

    // draws the closing options starting from (startX, startY) and shifting downwards by verticalShift after every option.
    void drawClosingOptions(int startY, int startX, int verticalShift);

    // calculates the new highlight, ie determines which option to highlight, depending on the user input
    void calculateNewHighlight(int choice);

public:

    // initializes the pointer to the open window and the window starting coordinates
    void initMenuWindow(WINDOW* win, int startY, int startX);

    // displays the whole menu
    void display();

    // returns the index of the option selected by the user
    int getChoice();

    void changeOptions(int choice);
};

#endif //SUPERALFABROS_MENUDISPLAYER_HPP
