#ifndef PACMAN_GAMEWINDOW_H
#define PACMAN_GAMEWINDOW_H


#include <ncurses.h>
#include "../../Model/Game.h"
#include "NcursesView.h"

class GameWindow
{
public:
    GameWindow(const std::string &mapFile, NcursesView &view);

    void takeControl();

private:
    void drawGame();

    Game game;
    WINDOW *window;
    NcursesView &view;

    uint16_t sizeX;
    uint16_t sizeY;
    uint16_t posX;
    uint16_t posY;

};


#endif //PACMAN_GAMEWINDOW_H
