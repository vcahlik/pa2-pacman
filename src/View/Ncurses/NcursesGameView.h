#ifndef PACMAN_GAMEWINDOW_H
#define PACMAN_GAMEWINDOW_H


#include <ncurses.h>
#include "../../Model/Game.h"
#include "NcursesUI.h"

class NcursesGameView
    : public GameView
{
public:
    NcursesGameView(const Game *game);

    virtual void show();

    virtual void redraw();

    virtual void end();

private:
    void drawWalls() const;

    void drawObjects() const;

    const Game *game;
    WINDOW *window;

    uint16_t sizeX;
    uint16_t sizeY;
    uint16_t posX;
    uint16_t posY;

};


#endif //PACMAN_GAMEWINDOW_H
