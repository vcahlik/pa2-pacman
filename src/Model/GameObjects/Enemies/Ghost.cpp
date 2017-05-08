#include "Ghost.h"
#include "../../../Config.h"
#include "../../Game.h"

Ghost::Ghost(const double posX, const double posY, const double speed, Game *game)
    : Enemy(posX, posY, speed, Config::GHOST_SIZE, game)
{
    chooseRandomDirection();
}

void Ghost::navigate()
{
    if (!isOnGrid())
    {
        return;
    }

    if (!isValidDirection(direction) || game->getMap().isIntersection(static_cast<uint32_t>(posX), static_cast<uint32_t>(posY)))
    {
        chooseRandomDirection();
    }
}
