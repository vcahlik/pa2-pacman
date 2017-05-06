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

class Game
{
public:
    explicit Game(const std::string &mapFilename);

    void performCycle();

    void performObjectActions();

    bool isObjectCollision(const GameObject &lhs, const GameObject &rhs);

    const GameMap &getMap() const;

    Player &getPlayer();

    const Player &getPlayer() const;

    const std::vector<std::unique_ptr<Coin>> &getCoins() const;

private:
    const GameMap map;
    Player player;
    std::vector<std::unique_ptr<Coin>> coins;

};


#endif //PACMAN_GAME_H
