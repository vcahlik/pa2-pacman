#ifndef PACMAN_NCURSESVIEW_H
#define PACMAN_NCURSESVIEW_H


#include "../../Model/Game.h"
#include "Color.h"
#include "../GameView.h"

class NcursesUI
{
public:
    virtual void show();

    const Color &getColors() const;

private:
    void initNcurses();

    void endNcurses();

    void displayGame();

    Color colors;
};


#endif //PACMAN_NCURSESVIEW_H
