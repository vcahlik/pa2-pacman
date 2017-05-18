#ifndef PACMAN_GAME_H
#define PACMAN_GAME_H


#include <cstdint>
#include <string>
#include <memory>
#include "GameMap.h"
#include "GameObjects/MovableObject.h"
#include "GameObjects/Player.h"
#include "GameObjects/Items/Item.h"
#include "GameObjects/Enemies/Enemy.h"
#include "GameObjects/Items/Coin.h"
#include "GameObjects/Enemies/Ghosts/Ghost.h"
#include "../UserConfig.h"
#include "GameTimer.h"
#include "GameObjects/Items/Cherry.h"
#include "GameObjects/Items/PowerUp.h"

class Game
{
public:
    enum class State
    {
        Running,
        LifeLost,
        GameOver,
        GameWon,
        Shutdown
    };

    explicit Game(const UserConfig userConfig);

    const State getState() const;

    void performCycle();

    const GameMap &getMap() const;

    Player &getPlayer();

    const Player &getPlayer() const;

    const std::vector<std::unique_ptr<Coin>> &getCoins() const;

    const std::vector<std::unique_ptr<Ghost>> &getGhosts() const;

    const std::vector<std::unique_ptr<PowerUp>> &getPowerUps() const;

    const uint32_t getRemainingLivesCount() const;

    void addScore(const uint32_t scored);

    const uint32_t getScore() const;

    const bool isCherryPresent() const;

    const Cherry &getCherry() const;

    void frightenGhosts();

    const Difficulty &getDifficulty() const;

private:
    void performStateRunningCycle();

    void performStateLifeLostCycle();

    void performStateGameOverCycle();

    void performStateGameWonCycle();

    void performObjectActions();

    void performContainerObjectsActions(std::vector<std::unique_ptr<GameObject>> &container);

    void removeDeletedObjects();

    void removeDeletedItems(std::vector<std::unique_ptr<Item>> &itemsContainer);

    void startWithNextLife();

    void placeCoins();

    void initGhosts();

    void placePowerUps();

    void performObjectGeneration();

    void performGhostsRelease();

    void performCherryGeneration();

    const bool ghostHouseEmpty() const;

    const GameMap map;
    std::unique_ptr<Player> player;

    std::vector<std::unique_ptr<Coin>> coins;
    std::vector<std::unique_ptr<Ghost>> ghosts;
    std::vector<std::unique_ptr<PowerUp>> powerUps;
    std::unique_ptr<Cherry> cherry;

    uint32_t remainingLivesCount;

    uint32_t score;

    GameTimer timer;

    const Difficulty difficulty;

    bool inShutdownState;

};


#endif //PACMAN_GAME_H
