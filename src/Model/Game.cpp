#include "Game.h"
#include "../Config.h"
#include "../Utils.h"

Game::Game(const UserConfig userConfig)
    : map(userConfig.getMapFileName()),
      player(new Player(map.getStartPosX(), map.getStartPosY(), this)),
      remainingLivesCount(Config::INITIAL_REMAINING_LIVES),
      difficulty(userConfig.getDifficulty()),
      inShutdownState(false)
{
    placeCoins();
}

const GameState Game::getState() const
{
    if (inShutdownState)
    {
        return GameState::Shutdown;
    } else if (coins.empty())
    {
        return GameState::GameWon;
    } else if (!player->isAlive())
    {
        if (remainingLivesCount > 0 )
        {
            return GameState::LifeLost;
        } else
        {
            return GameState::GameOver;
        }
    } else
    {
        return GameState::Running;
    }
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

const uint32_t Game::getRemainingLivesCount() const
{
    return remainingLivesCount;
}

void Game::addScore(const uint32_t scored)
{
    score += scored;
}

const uint32_t Game::getScore() const
{
    return score;
}

const bool Game::isCherryPresent() const
{
    return cherry.get() != nullptr;
}

const Cherry &Game::getCherry() const
{
    if (!isCherryPresent())
    {
        throw std::runtime_error("called getCherry() without checking isCherryPresent()");
    }

    return *cherry.get();
}

void Game::performCycle()
{
    if (getState() == GameState::Shutdown)
    {
        return;
    }

    timer.notifyOfNextCycle();

    switch (getState())
    {
        case GameState::Running:
            performStateRunningCycle();
            break;
        case GameState::LifeLost:
            performStateLifeLostCycle();
            break;
        case GameState::GameOver:
            performStateGameOverCycle();
            break;
        case GameState::GameWon:
            performStateGameWonCycle();
            break;
        default:
            throw std::logic_error("unhandled state");
    }
}

void Game::performStateRunningCycle()
{
    performObjectGeneration();
    performObjectActions();
}

void Game::performStateLifeLostCycle()
{
    timer.requestTimer(Timeout::StateLifeLost);
    if (timer.isTimeoutEvent(Timeout::StateLifeLost))
    {
        --remainingLivesCount;
        startWithNextLife();
    }
}

void Game::performStateGameOverCycle()
{
    timer.requestTimer(Timeout::StateGameOver);
    if (timer.isTimeoutEvent(Timeout::StateGameOver))
    {
        inShutdownState = true;
    }
}

void Game::performStateGameWonCycle()
{
    timer.requestTimer(Timeout::StateGameWon);
    if (timer.isTimeoutEvent(Timeout::StateGameWon))
    {
        inShutdownState = true;
    }
}

void Game::performObjectActions()
{
    player->performActions();

    performContainerObjectsActions(reinterpret_cast<std::vector<std::unique_ptr<GameObject>> &>(coins));
    performContainerObjectsActions(reinterpret_cast<std::vector<std::unique_ptr<GameObject>> &>(ghosts));

    if (isCherryPresent())
    {
        performSingleObjectActions(reinterpret_cast<std::unique_ptr<GameObject> &>(cherry));
    }
}

void Game::performContainerObjectsActions(std::vector<std::unique_ptr<GameObject>> &container)
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

void Game::performSingleObjectActions(std::unique_ptr<GameObject> &gameObject)
{
    if (!gameObject->performActions())
    {
        gameObject.reset();
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

void Game::performObjectGeneration()
{
    performGhostGeneration();
    performCherryGeneration();
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

void Game::performCherryGeneration()
{
    if (!isCherryPresent())
    {
        timer.requestTimer(Timeout::CherryGeneration);
        if (timer.isTimeoutEvent(Timeout::CherryGeneration))
        {
            uint32_t posX = 0;
            uint32_t posY = 0;
            while (true)
            {
                posX = Utils::getRandom(map.sizeX());
                posY = Utils::getRandom(map.sizeY());
                if (map.squareCanBeEntered(posX, posY))
                {
                    break;
                }
            }
            cherry.reset(new Cherry(posX, posY, this));
        }
    }
}

void Game::addGhost()
{
    uint32_t x = map.getSpawnPointX();
    uint32_t y = map.getSpawnPointY();
    ghosts.push_back(std::unique_ptr<Ghost>(new Ghost(x, y, Config::GHOST_BASE_SPEED, this)));
}
