#ifndef PACMAN_GAMECONTROLLER_H
#define PACMAN_GAMECONTROLLER_H


#include <bits/unique_ptr.h>
#include "../View/Ncurses/NcursesUI.h"
#include "../View/GameView.h"

class GameController
{
public:
    GameController(Game *game, GameView *view);

    void startGame();

private:
    Game *game;
    GameView *view;

    void gameLoop();

    void performCycle();

    void processUserInput();

};


#endif //PACMAN_GAMECONTROLLER_H
