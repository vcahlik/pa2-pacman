#ifndef PACMAN_GAMEWINDOW_H
#define PACMAN_GAMEWINDOW_H


#include <ncurses.h>
#include "../../Model/Game.h"
#include "NcursesUI.h"
#include "../../Model/GameObjects/Items/Coin.h"

class NcursesGameView
    : public GameView
{
public:
    explicit NcursesGameView(const Game *game);

    virtual void show() override;

    virtual void redraw() override;

    virtual void end() override;

    virtual const InputKey getPressedKey() const;

private:
    void drawWalls() const;

    void drawGameObjects() const;

    void drawObject(const Player &player) const;

    void drawObject(const Coin &coin) const;

    void drawTextGraphics(const char * const text, const uint32_t lineNo, const double x, const double y, const Color color) const;

    const Game *game;
    WINDOW *window;

    uint32_t sizeX;
    uint32_t sizeY;
    uint32_t posX;
    uint32_t posY;

};


#endif //PACMAN_GAMEWINDOW_H
