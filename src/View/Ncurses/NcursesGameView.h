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
    void drawBorder() const;

    void drawStatusBar() const;

    void drawMap() const;

    void drawWall(const Coordinates coord) const;

    void drawTeleport(const Coordinates coord) const;

    void drawSpawnPoint(const Coordinates coord) const;

    void drawGameObjects() const;

    void drawObject(const Player &player) const;

    void drawObject(const Coin &coin) const;

    void drawObject(const Cherry &cherry) const;

    void drawObject(const Ghost &ghost) const;

    void drawTextGraphics(const char * const text, const uint32_t lineNo, const Position position, const Color color) const;

    const Game *game;
    WINDOW *window;

    uint32_t sizeX;
    uint32_t sizeY;
    uint32_t posX;
    uint32_t posY;

};


#endif //PACMAN_GAMEWINDOW_H
