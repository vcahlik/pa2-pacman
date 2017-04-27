#include "GameController.h"
#include "../Config.h"
#include <unistd.h>

GameController::GameController(Game *game, GameView *view)
        : game(game), view(view)
{

}

void GameController::startGame()
{
    view->show();

    gameLoop();

    view->end();
}

void GameController::gameLoop()
{
    while (true)
    {
        performCycle();
        usleep(Config::REFRESH_TIME_USECS);
    }
}

void GameController::performCycle()
{
    game->performCycle();
    view->redraw();
}
