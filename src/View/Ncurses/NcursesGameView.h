#ifndef PACMAN_GAMEWINDOW_H
#define PACMAN_GAMEWINDOW_H


#include <ncurses.h>
#include "../../Model/Game.h"
#include "NcursesUI.h"
#include "../../Model/GameObjects/Items/Coin.h"

/**
 * @brief Concrete implementation of GameView
 */
class NcursesGameView
    : public GameView
{
public:
    explicit NcursesGameView(const Game *game);

    virtual void show() override;

    virtual void redraw() override;

    virtual void end() override;

    virtual const InputKey getPressedKey() const override;

private:
    /**
     * @brief Draws a fancy border along the game window
     */
    void drawBorder() const;

    /**
     * @brief Draws a status bar with the player's score, life counter...
     */
    void drawStatusBar() const;

    /**
     * @brief Draws the game board
     */
    void drawMap() const;

    void drawWall(const Coordinates coord) const;

    void drawTeleport(const Coordinates coord) const;

    void drawSpawnPoint(const Coordinates coord) const;

    /**
     * @brief Draws all the game's GameObjects
     * @param coord
     */
    void drawGameObjects() const;

    void drawObject(const Player &player) const;

    void drawObject(const Coin &coin) const;

    void drawObject(const Cherry &cherry) const;

    void drawObject(const Ghost &ghost) const;

    void drawObject(const PowerUp &powerUp) const;

    /**
     * @brief Draws a single line of some graphics (usually GameObject or a map square)
     * @param text
     * @param lineNo Line number if the graphics spans multiple lines, starts with 1
     * @param position
     * @param color
     */
    void drawTextGraphics(const char * const text, const uint32_t lineNo, const Position position, const Color color) const;

    const Game *game;
    WINDOW *window;

    uint32_t sizeX; /**< @brief Total canvas size axis X */
    uint32_t sizeY; /**< @brief Total canvas size axis Y */
    uint32_t posX;
    uint32_t posY;

};


#endif //PACMAN_GAMEWINDOW_H
