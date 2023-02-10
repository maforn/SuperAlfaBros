//
// Created by vboxuser on 24.01.23.
//

#include "MenuDisplayer.hpp"

void MenuDisplayer::initTopPart(wstring title, wstring topRows[], int topRowsCount) {
    this->title = title;

    this->topRowsCount = min(topRowsCount, MAX_TOP_ROWS);
    copyStrings(topRows, this->topRows, this->topRowsCount);
}

void MenuDisplayer::initOptions(wstring options[], int optionsCount, wstring closingOpt[], int closingOptCount) {
    this->optionsCount = min(optionsCount, MAX_OPTIONS);
    copyStrings(options, this->options, this->optionsCount);

    this->closingOptCount = min(closingOptCount, MAX_CLOSING);
    copyStrings(closingOpt, this->closingOptions, this->closingOptCount);
}

void MenuDisplayer::printTitle() {
    //title needs to be printed one line at the time in order to appear in the correct position.

    // start index = first index of current line, current index = index of the currently analyzed character
    int startIndex = 0, currentIndex = 0, length = (this->title).length();

    // go through the title one character at the time
    while(currentIndex < length){
        //if end of line is reached, print the last read line and increment lastY to print in lower line next time
        if((this->title)[currentIndex] == '\n'){
            wstring subStr = (this->title).substr(startIndex, currentIndex - startIndex);
            mvwaddwstr(this->win, this->lastY, this->menuStartX, subStr.c_str());
            this->lastY += 1;
            startIndex = currentIndex + 1;
        }
        currentIndex += 1;
    }
}

void MenuDisplayer::drawTopPart() {
    printTitle();
    this->lastY += VERTICAL_SPACING;

    for(int i = 0; i < this->topRowsCount; i++){
        this->lastY += VERTICAL_SPACING;
        mvwaddwstr(win, lastY, menuStartX, topRows[i].c_str());
    }
    wrefresh(this->win);
}

void MenuDisplayer::drawAllOptions() {
    int startY = this->lastY + 1;
    int verticalShift = 1;

    drawOptions(startY, this->menuStartX, verticalShift);
    startY += (verticalShift * (this->optionsCount) + VERTICAL_SPACING);
    drawClosingOptions(startY, this->menuStartX, verticalShift);
}

void MenuDisplayer::drawOptions(int startY, int startX, int verticalShift) {
    for(int i = 0; i < this->optionsCount; i++){
        if(i == this->highlight)
            wattron(win, A_REVERSE); // turn highlight on
        mvwaddwstr(win, startY + i*verticalShift, startX, options[i].c_str());
        wattroff(win, A_REVERSE); // turn highlight off
    }
}

void MenuDisplayer::drawClosingOptions(int startY, int startX, int verticalShift) {
    for(int i = 0; i < this->closingOptCount; i++){
        if(i + this->optionsCount == this->highlight)
            wattron(win, A_REVERSE); // turn highlight on
        mvwaddwstr(win, startY + i*verticalShift, startX, closingOptions[i].c_str());
        wattroff(win, A_REVERSE); // turn highlight off
    }
}

int MenuDisplayer::calculateNewHighlight(int choice) {
    switch(choice){
        case KEY_UP:
            this->highlight -= 1;
            break;
        case KEY_DOWN:
            this->highlight += 1;
            break;
        default:
            break;
    }

    int totalOptCount = this->optionsCount + this->closingOptCount;
    int newHighlight = (totalOptCount + this->highlight) % totalOptCount; //maintain highlight within option range
    return newHighlight;
}

//PUBLIC

void MenuDisplayer::initMenuWindow(WINDOW *win, int startY, int startX) {
    this->win = win;
    this->menuStartY = startY;
    this->menuStartX = startX;
}

void MenuDisplayer::display() {
    // clear window and draw outlining box
    wclear(this->win);
    box(this->win, 0, 0);

    // draw menu
    this->lastY = this->menuStartY;
    drawTopPart();
    drawAllOptions();

    // refresh window
    wrefresh(this->win);
}

int MenuDisplayer::getChoice() {
    return(this->highlight);
}

void MenuDisplayer::changeSelectedOption(int choice) {
    this->highlight = calculateNewHighlight(choice);
}