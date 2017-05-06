#include "Game.h"
#include "GameObjects/Items/Coin.h"

Game::Game(const std::string &mapFilename)
    : map(mapFilename),
      player(map.getStartPosX(), map.getStartPosY(), this)
{
    for (uint32_t x = 0; x < map.sizeX(); ++x)
    {
        for (uint32_t y = 0; y < map.sizeY(); ++y)
        {
            if (map.getSquareType(x, y) == SquareType::Space)
            {
                coins.push_back(std::unique_ptr<Coin>(new Coin(x, y, this)));
            }
        }
    }
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

const std::vector<std::unique_ptr<Coin>> &Game::getCoins() const
{
    return coins;
}

void Game::performCycle()
{
    performObjectActions();
}

void Game::performObjectActions()
{
    player.performActions();

    for (auto it = coins.begin(); it != coins.end(); )
    {
        auto &coin = *it;
        if (!coin->performActions())
        {
            it = coins.erase(it);
        } else
        {
            ++it;
        }
    }
}

bool Game::isObjectCollision(const GameObject &lhs, const GameObject &rhs)
{
    return (lhs.getPosX() + lhs.getSize() > rhs.getPosX() &&
            lhs.getPosX() < rhs.getPosX() + rhs.getSize() &&
            lhs.getPosY() + lhs.getSize() > rhs.getPosY() &&
            lhs.getPosY() < rhs.getPosY() + rhs.getSize());
}
