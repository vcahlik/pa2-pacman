#ifndef PACMAN_GAME_H
#define PACMAN_GAME_H


#include <cstdint>
#include <string>
#include "GameMap.h"
#include "GameObjects/MovableObject.h"
#include "GameObjects/Player.h"

class Game
{
public:
    Game(const std::string &mapFilename);

    void performCycle();

    void performObjectActions();

    void checkObjectCollisions();

    const GameMap &getMap() const;

    const Player &getPlayer() const;

private:
    const GameMap map;

    Player player;

};


#endif //PACMAN_GAME_H
