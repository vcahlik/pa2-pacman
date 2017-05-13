#include <cstdlib>
#include <stdexcept>
#include "Enemy.h"
#include "../../../Utils.h"
#include "../Items/Item.h"
#include "../../Game.h"

Enemy::Enemy(const double posX, const double posY, const double speed, const double size, Game *game)
        : MovableObject(posX, posY, speed, size, game)
{

}

void Enemy::chooseRandomDirection()
{
    Direction newDirection;

    while (true)
    {
        newDirection = getRandomValidDirection();

        if (Utils::areOppositeDirections(direction, newDirection) &&
            !isOnlyValidDirection(newDirection))
        {
            continue;
        }

        direction = newDirection;
        return;
    }
}

const bool Enemy::performActions()
{
    MovableObject::performActions();

    if (game->isObjectCollision(*this, game->getPlayer()))
    {
        game->getPlayer().die();
    }

    return true;
}
