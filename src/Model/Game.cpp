#include "Game.h"
#include "../Config.h"

Game::Game(const UserConfig userConfig)
    : map(userConfig.getMapFileName()),
      player(new Player(map.getStartPosX(), map.getStartPosY(), this)),
      remainingLives(Config::INITIAL_REMAINING_LIVES),
      difficulty(userConfig.getDifficulty()),
      finished(false)
{
    placeCoins();
}

const bool Game::isFinished() const
{
    return finished;
}

const bool Game::isRunning() const
{
    return (player->isAlive() && !coins.empty());
}

const GameMap &Game::getMap() const
{
    return map;
}

Player &Game::getPlayer()
{
    return *player;
}

const Player &Game::getPlayer() const
{
    return *player;
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
    if (finished)
    {
        return;
    }

    timer.notifyOfNextCycle();

    if (isRunning())
    {
        performGhostGeneration();
        performObjectActions();
    } else
    {
        performTimeoutEvent();
    }
}

void Game::performObjectActions()
{
    player->performActions();

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

void Game::performTimeoutEvent()
{
    if (!player->isAlive())
    {
        performPlayerDeathEvent();
    } else if (coins.empty())
    {
        performPlayerVictoryEvent();
    }
}

void Game::performPlayerDeathEvent()
{
    if (remainingLives > 0)
    {
        // Round over
        timer.requestTimer(Timeout::PlayerDeathScreen);
        if (timer.isTimeoutEvent(Timeout::PlayerDeathScreen))
        {
            --remainingLives;
            startWithNextLife();
        }
    } else
    {
        // Game over
        timer.requestTimer(Timeout::GameOverScreen);
        if (timer.isTimeoutEvent(Timeout::GameOverScreen))
        {
            finished = true;
        }
    }
}

void Game::performPlayerVictoryEvent()
{
    if (timer.isTimeoutEvent(Timeout::PlayerVictoryScreen))
    {
        finished = true;
    }
}

void Game::startWithNextLife()
{
    player.reset(new Player(map.getStartPosX(), map.getStartPosY(), this));

    ghosts.clear();
}

bool Game::isObjectCollision(const GameObject &lhs, const GameObject &rhs)
{
    return (lhs.getPosX() + lhs.getSize() > rhs.getPosX() &&
            lhs.getPosX() < rhs.getPosX() + rhs.getSize() &&
            lhs.getPosY() + lhs.getSize() > rhs.getPosY() &&
            lhs.getPosY() < rhs.getPosY() + rhs.getSize());
}

void Game::placeCoins()
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

void Game::performGhostGeneration()
{
    if (ghosts.size() < Config::GHOST_COUNT)
    {
        timer.requestTimer(Timeout::GhostGeneration);
        if (timer.isTimeoutEvent(Timeout::GhostGeneration))
        {
            addGhost();
        }
    }
}

void Game::addGhost()
{
    uint32_t x = map.getSpawnPointX();
    uint32_t y = map.getSpawnPointY();
    ghosts.push_back(std::unique_ptr<Ghost>(new Ghost(x, y, Config::GHOST_BASE_SPEED, this)));
}
