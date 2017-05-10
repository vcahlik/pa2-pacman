#include "Game.h"
#include "../Config.h"

Game::Game(const UserConfig userConfig)
    : map(userConfig.getMapFileName()),
      player(map.getStartPosX(), map.getStartPosY(), this),
      difficulty(userConfig.getDifficulty())
{
    generateCoins();
    addGhost();
    addGhost();
}

const bool Game::isVictory() const
{
    return coins.empty();
}

const bool Game::isGameOver() const
{
    return !player.isAlive();
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

const std::vector<std::unique_ptr<Ghost>> &Game::getGhosts() const
{
    return ghosts;
}

void Game::performCycle()
{
    performObjectActions();
}

void Game::performObjectActions()
{
    player.performActions();

    performContainerActions(reinterpret_cast<std::vector<std::unique_ptr<GameObject>> &>(coins));
    performContainerActions(reinterpret_cast<std::vector<std::unique_ptr<GameObject>> &>(ghosts));
}

void Game::performContainerActions(std::vector<std::unique_ptr<GameObject>> &container)
{
    for (auto it = container.begin(); it != container.end(); )
    {
        auto &gameObject = *it;
        if (!gameObject->performActions())
        {
            it = container.erase(it);
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

void Game::generateCoins()
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

void Game::addGhost()
{
    uint32_t x = map.getSpawnPointX();
    uint32_t y = map.getSpawnPointY();
    ghosts.push_back(std::unique_ptr<Ghost>(new Ghost(x, y, Config::GHOST_BASE_SPEED, this)));
}
