#ifndef PACMAN_GAME_H
#define PACMAN_GAME_H


#include <cstdint>
#include <string>
#include "GameMap.h"

class Game
{
public:
    Game(const std::string &mapFilename);

    void start();

    void performCycle();

    void performObjectActions();

    void checkObjectCollisions();

    const GameMap &getMap();

private:
    const GameMap map;
};


#endif //PACMAN_GAME_H
