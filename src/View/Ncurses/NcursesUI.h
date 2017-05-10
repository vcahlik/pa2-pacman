#ifndef PACMAN_NCURSESVIEW_H
#define PACMAN_NCURSESVIEW_H


#include <ncurses.h>
#include "../../Model/Game.h"
#include "Color.h"
#include "../GameView.h"
#include "../../UserConfig.h"

class NcursesUI
{
public:
    virtual void show(const UserConfig userConfig);

private:
    WINDOW *console;
};


#endif //PACMAN_NCURSESVIEW_H
