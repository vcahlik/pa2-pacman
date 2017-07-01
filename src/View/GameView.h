#ifndef PACMAN_VIEW_H
#define PACMAN_VIEW_H


#include "InputKey.h"

/**
 * @brief Abstract view part of the game's MVC architecture
 */
class GameView
{
public:
    /**
     * @brief Displays the game
     */
    virtual void show() = 0;

    /**
     * @brief Redraws the model
     */
    virtual void redraw() = 0;

    /**
     * @brief Removes the game from screen
     */
    virtual void end() = 0;

    /**
     * @brief Checks for user input and returns it or throws
     * @return
     * @throws NoUserInputException if no input
     */
    virtual const InputKey getPressedKey() const = 0;
};


#endif //PACMAN_VIEW_H
