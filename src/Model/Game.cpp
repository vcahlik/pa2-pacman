#include "Game.h"

Game::Game(const std::string &mapFilename)
    : map(mapFilename)
{

}

const GameMap &Game::getMap()
{
    return map;
}
