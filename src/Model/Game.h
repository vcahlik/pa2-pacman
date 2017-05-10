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
#include "GameObjects/Enemies/Ghost.h"
#include "../UserConfig.h"
#include "GameTimer.h"

class Game
{
public:
    explicit Game(const UserConfig userConfig);

    void performCycle();

    const bool isFinished() const;

    const bool isRunning() const;

    bool isObjectCollision(const GameObject &lhs, const GameObject &rhs);

    const GameMap &getMap() const;

    Player &getPlayer();

    const Player &getPlayer() const;

    const std::vector<std::unique_ptr<Coin>> &getCoins() const;

    const std::vector<std::unique_ptr<Ghost>> &getGhosts() const;

private:
    void performObjectActions();

    void performContainerActions(std::vector<std::unique_ptr<GameObject>> &container);

    void performTimeoutEvent();

    void performPlayerDeathEvent();

    void performPlayerVictoryEvent();

    void startWithNextLife();

    void placeCoins();

    void performGhostGeneration();

    void addGhost();

    const GameMap map;
    std::unique_ptr<Player> player;

    std::vector<std::unique_ptr<Coin>> coins;
    std::vector<std::unique_ptr<Ghost>> ghosts;

    uint32_t remainingLives;

    GameTimer timer;

    const Difficulty difficulty;

    bool finished;

};


#endif //PACMAN_GAME_H
