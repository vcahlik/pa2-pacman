#ifndef PACMAN_GAMECONTROLLER_H
#define PACMAN_GAMECONTROLLER_H


#include <bits/unique_ptr.h>
#include "../View/Ncurses/NcursesUI.h"
#include "../View/GameView.h"
#include "../Model/Game.h"

/**
 * @brief Controller part of the game's MVC architecture
 */
class GameController
{
public:
    explicit GameController(Game *game, GameView *view);

    /**
     * @brief Gives control to the controller and starts the model
     */
    void startGame();

private:
    Game *game;
    GameView *view;

    /**
     * @brief The main control loop, run until the game gets to shutdown state
     */
    void gameLoop();

    /**
     * @brief Single cycle - gets user input, updates model, redraws view
     */
    void performCycle();

    /**
     * @brief Checks user input and possibly gives it to model
     */
    void processUserInput();

};


#endif //PACMAN_GAMECONTROLLER_H
