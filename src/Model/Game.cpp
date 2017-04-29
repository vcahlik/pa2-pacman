#include "Game.h"

Game::Game(const std::string &mapFilename)
    : map(mapFilename),
      player(map.getStartPosX(), map.getStartPosY(), this)
{

}

const GameMap &Game::getMap() const
{
    return map;
}

Player &Game::getPlayer()
{
    return player;
}

const Player &Game::getPlayer() const
{
    return player;
}

void Game::performCycle()
{
    performObjectActions();
    checkObjectCollisions();
}

void Game::performObjectActions()
{
    player.performActions();
}

void Game::checkObjectCollisions()
{

}
