#ifndef PACMAN_NCURSESVIEW_H
#define PACMAN_NCURSESVIEW_H


#include <ncurses.h>
#include "Color.h"
#include "View/GameView.h"
#include "LevelConfig.h"

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
    virtual void show(const LevelConfig userConfig);

private:
    WINDOW *console;
};


#endif //PACMAN_NCURSESVIEW_H
