#ifndef PACMAN_NCURSESVIEW_H
#define PACMAN_NCURSESVIEW_H


#include <ncurses.h>
#include "Color.h"
#include "../GameView.h"
#include "../../UserConfig.h"

/**
 * @brief "Graphical" Ncurses UI
 */
class NcursesUI
{
public:
    /**
     * @brief Takes control and starts the game's MVC components
     * @param userConfig
     * @throws Utils::ExceptionMessage rethrown, ends Ncurses
     */
    virtual void show(const UserConfig userConfig);

private:
    WINDOW *console;
};


#endif //PACMAN_NCURSESVIEW_H
