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

class Game
{
public:
    explicit Game(const UserConfig userConfig);

    void performCycle();

    const bool isVictory() const;

    const bool isGameOver() const;

    bool isObjectCollision(const GameObject &lhs, const GameObject &rhs);

    const GameMap &getMap() const;

    Player &getPlayer();

    const Player &getPlayer() const;

    const std::vector<std::unique_ptr<Coin>> &getCoins() const;

    const std::vector<std::unique_ptr<Ghost>> &getGhosts() const;

private:
    void performObjectActions();

    void performContainerActions(std::vector<std::unique_ptr<GameObject>> &container);

    void generateCoins();
    void addGhost();

    const GameMap map;
    Player player;

    std::vector<std::unique_ptr<Coin>> coins;
    std::vector<std::unique_ptr<Ghost>> ghosts;

    const Difficulty difficulty;
};


#endif //PACMAN_GAME_H
