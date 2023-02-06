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
    int startIndex = 0, currentIndex = 0, length = (this->title).length();
    while(currentIndex < length){
        if((this->title)[currentIndex] == '\n'){
            wstring subStr = (this->title).substr(startIndex, currentIndex - startIndex);
            mvwaddwstr(this->win, this->lastY, this->menuStartX, subStr.c_str());
            this->lastY += 1;
            startIndex = currentIndex+ 1;
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
            wattron(win, A_REVERSE);
        mvwaddwstr(win, startY + i*verticalShift, startX, options[i].c_str());
        wattroff(win, A_REVERSE);
    }
}

void MenuDisplayer::drawClosingOptions(int startY, int startX, int verticalShift) {
    for(int i = 0; i < this->closingOptCount; i++){
        if(i + this->optionsCount == this->highlight)
            wattron(win, A_REVERSE);
        mvwaddwstr(win, startY + i*verticalShift, startX, closingOptions[i].c_str());
        wattroff(win, A_REVERSE);
    }
}

void MenuDisplayer::calculateNewHighlight(int choice) {
    switch(choice){
        case KEY_UP: this->highlight -= 1; break;
        case KEY_DOWN: this->highlight += 1; break;
        default: break;
    }

    int totalOptCount = this->optionsCount + this->closingOptCount;
    this->highlight = (totalOptCount + this->highlight) % totalOptCount; //maintain highlight within option range
}


//PUBLIC

void MenuDisplayer::initMenuWindow(WINDOW *win, int startY, int startX) {
    this->win = win;
    this->menuStartY = startY;
    this->menuStartX = startX;
}

void MenuDisplayer::display() {
    wclear(this->win);
    box(this->win, 0, 0);

    this->lastY = this->menuStartY;
    drawTopPart();
    drawAllOptions();

    wrefresh(this->win);
}

int MenuDisplayer::getChoice() {
    int choice;
    bool choiceMade = false;

    while(!choiceMade){
        choice = wgetch(win);
        if(choice == 10)
            choiceMade = true;
        else{
            calculateNewHighlight(choice);
            drawAllOptions();
        }
    }
    return(this->highlight);
}