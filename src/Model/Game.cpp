#include "Game.h"
#include "GameObjects/Enemies/Ghosts/AggressiveGhost.h"
#include "GameObjects/Enemies/Ghosts/NormalGhost.h"
#include "GameObjects/Enemies/Ghosts/FreakGhost.h"

Game::Game(const LevelConfig userConfig)
        : map(userConfig.getMapFileName()),
          player(std::make_unique<Player>(map.getStartPosCoordinates(), this)),
          score(0),
          timer(this),
          difficulty(userConfig.getDifficultyLevel()),
          inShutdownState(false) {
    placeCoins();
    initGhosts();
    placePowerUps();
    remainingLivesCount = difficulty.getInitialRemainingLives();
}

const Game::State Game::getState() const {
    if (inShutdownState) {
        return State::Shutdown;
    } else if (coins.empty()) {
        return State::GameWon;
    } else if (!player->isAlive()) {
        if (remainingLivesCount > 0) {
            return State::LifeLost;
        } else {
            return State::GameOver;
        }
    } else {
        return State::Running;
    }
}

const GameMap &Game::getMap() const {
    return map;
}

Player &Game::getPlayer() {
    return *player;
}

const Player &Game::getPlayer() const {
    return *player;
}

const std::vector<std::unique_ptr<Coin>> &Game::getCoins() const {
    return coins;
}

const std::vector<std::unique_ptr<Ghost>> &Game::getGhosts() const {
    return ghosts;
}

const std::vector<std::unique_ptr<PowerUp>> &Game::getPowerUps() const {
    return powerUps;
}

const uint32_t Game::getRemainingLivesCount() const {
    return remainingLivesCount;
}

void Game::increaseScore(const uint32_t scored) {
    score += scored;
}

const uint32_t Game::getScore() const {
    return score;
}

const bool Game::isCherryPresent() const {
    return cherry.get() != nullptr;
}

const Cherry &Game::getCherry() const {
    if (!isCherryPresent()) {
        throw std::runtime_error("called getCherry() without checking isCherryPresent()");
    }

    return *cherry.get();
}

void Game::frightenGhosts() {
    for (auto &ghost : ghosts) {
        ghost->frighten();
    }
}

void Game::performCycle() {
    if (getState() == State::Shutdown) {
        return;
    }

    timer.notifyOfNextCycle();

    switch (getState()) {
        case State::Running:
            performStateRunningCycle();
            break;
        case State::LifeLost:
            performStateLifeLostCycle();
            break;
        case State::GameOver:
            performStateGameOverCycle();
            break;
        case State::GameWon:
            performStateGameWonCycle();
            break;
        default:
            throw std::logic_error("unhandled state");
    }
}

void Game::performStateRunningCycle() {
    performObjectGeneration();
    performObjectActions();
    removeDeletedObjects();
}

void Game::performStateLifeLostCycle() {
    timer.requestTimer(TimeoutEvent::GameStateLifeLost);
    if (timer.isTimeoutEvent(TimeoutEvent::GameStateLifeLost)) {
        --remainingLivesCount;
        startWithNextLife();
    }
}

void Game::performStateGameOverCycle() {
    timer.requestTimer(TimeoutEvent::GameStateGameOver);
    if (timer.isTimeoutEvent(TimeoutEvent::GameStateGameOver)) {
        inShutdownState = true;
    }
}

void Game::performStateGameWonCycle() {
    timer.requestTimer(TimeoutEvent::GameStateGameWon);
    if (timer.isTimeoutEvent(TimeoutEvent::GameStateGameWon)) {
        inShutdownState = true;
    }
}

void Game::performObjectActions() {
    player->performActions();

    performContainerObjectsActions(reinterpret_cast<std::vector<std::unique_ptr<GameObject>> &>(coins));
    performContainerObjectsActions(reinterpret_cast<std::vector<std::unique_ptr<GameObject>> &>(ghosts));
    performContainerObjectsActions(reinterpret_cast<std::vector<std::unique_ptr<GameObject>> &>(powerUps));

    if (isCherryPresent()) {
        cherry->performActions();
    }
}

void Game::performContainerObjectsActions(std::vector<std::unique_ptr<GameObject>> &container) {
    for (auto it = container.begin(); it != container.end(); ++it) {
        auto &gameObject = *it;
        gameObject->performActions();
    }
}

void Game::removeDeletedObjects() {
    removeDeletedItems(reinterpret_cast<std::vector<std::unique_ptr<Item>> &>(coins));
    removeDeletedItems(reinterpret_cast<std::vector<std::unique_ptr<Item>> &>(powerUps));

    for (auto it = coins.begin(); it != coins.end();) {
        auto &coin = *it;
        if (coin->getState() == Item::State::Removed) {
            it = coins.erase(it);
        } else {
            ++it;
        }
    }

    if (isCherryPresent() && cherry->getState() == Item::State::Removed) {
        cherry.reset();
    }
}

void Game::removeDeletedItems(std::vector<std::unique_ptr<Item>> &itemsContainer) {
    for (auto it = itemsContainer.begin(); it != itemsContainer.end();) {
        auto &coin = *it;
        if (coin->getState() == Item::State::Removed) {
            it = itemsContainer.erase(it);
        } else {
            ++it;
        }
    }
}

void Game::startWithNextLife() {
    player = std::make_unique<Player>(map.getStartPosCoordinates(), this);

    for (auto &ghost : ghosts) {
        ghost->reset();
    }

    timer.stopTimer(TimeoutEvent::GhostGeneration);
}

void Game::placeCoins() {
    for (uint32_t x = 0; x < map.getSizeX(); ++x) {
        for (uint32_t y = 0; y < map.getSizeY(); ++y) {
            Coordinates coord(x, y);
            if (map.getSquareType(coord) == SquareType::Space) {
                coins.push_back(std::make_unique<Coin>(coord, this));
            }
        }
    }
}

void Game::initGhosts() {
    ghosts.push_back(std::make_unique<NormalGhost>(this));
    ghosts.push_back(std::make_unique<AggressiveGhost>(this));
    ghosts.push_back(std::make_unique<FreakGhost>(this));
    ghosts.push_back(std::make_unique<AggressiveGhost>(this));
}

void Game::placePowerUps() {
    for (const Coordinates &coord : map.getPowerUpLocations()) {
        powerUps.push_back(std::make_unique<PowerUp>(coord, this));
    }
}

void Game::performObjectGeneration() {
    performGhostsRelease();
    performCherryGeneration();
}

void Game::performGhostsRelease() {
    if (ghostHouseEmpty()) {
        return;
    }

    timer.requestTimer(TimeoutEvent::GhostGeneration);
    if (!timer.isTimeoutEvent(TimeoutEvent::GhostGeneration)) {
        return;
    }

    // Unleash a single ghost
    for (auto &ghost : ghosts) {
        if (ghost->getState() == Ghost::State::InGhostHouse) {
            ghost->releaseFromGhostHouse();
            return;
        }
    }
}

void Game::performCherryGeneration() {
    if (!isCherryPresent()) {
        timer.requestTimer(TimeoutEvent::CherryGeneration);
        if (timer.isTimeoutEvent(TimeoutEvent::CherryGeneration)) {
            cherry = std::make_unique<Cherry>(this);
        }
    }
}

const bool Game::ghostHouseEmpty() const {
    for (auto &ghost : ghosts) {
        if (ghost->getState() == Ghost::State::InGhostHouse) {
            return false;
        }
    }

    return true;
}

const Difficulty &Game::getDifficulty() const {
    return difficulty;
}
