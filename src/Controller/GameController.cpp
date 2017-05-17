#include "GameController.h"
#include "../Config.h"
#include "../InputKey.h"
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
    while (game->getState() != Game::State::Shutdown)
    {
        performCycle();
        usleep(static_cast<uint32_t>(Config::CYCLE_TIME_MSECS) * 1000);
    }
}

void GameController::performCycle()
{
    processUserInput();
    game->performCycle();
    view->redraw();
}

void GameController::processUserInput()
{
    InputKey key = InputKey::UP;

    try
    {
        key = view->getPressedKey();
    } catch (NoUserInputException &e)
    {
        return;
    }

    switch (key)
    {
        case InputKey::UP:
            game->getPlayer().requestGoUp();
            break;
        case InputKey::DOWN:
            game->getPlayer().requestGoDown();
            break;
        case InputKey::LEFT:
            game->getPlayer().requestGoLeft();
            break;
        case InputKey::RIGHT:
            game->getPlayer().requestGoRight();
            break;
        default:
            break;
    }
}
