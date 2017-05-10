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
    Direction newDirection = Direction::UP;

    while (true)
    {
        int32_t random = Utils::getRandom(4);
        switch (random)
        {
            case 0:
                newDirection = Direction::UP;
                break;
            case 1:
                newDirection = Direction::DOWN;
                break;
            case 2:
                newDirection = Direction::LEFT;
                break;
            case 3:
                newDirection = Direction::RIGHT;
                break;
            default:
                throw std::logic_error("random range: incorrect implementation");
        }

        if (isValidDirection(newDirection))
        {
            if (Utils::areOppositeDirections(direction, newDirection) &&
                !onlyPossibleDirection(newDirection))
            {
                continue;
            }

            direction = newDirection;
            return;
        }
    }
}

const bool Enemy::onlyPossibleDirection(const Direction newDirection) const
{
    if (!isValidDirection(newDirection))
    {
        throw std::logic_error("given direction is not valid");
    }

    switch (newDirection)
    {
        case Direction::UP:
            return (!isValidDirection(Direction::DOWN) &&
                    !isValidDirection(Direction::LEFT) &&
                    !isValidDirection(Direction::RIGHT));
        case Direction::DOWN:
            return (!isValidDirection(Direction::UP) &&
                    !isValidDirection(Direction::LEFT) &&
                    !isValidDirection(Direction::RIGHT));
        case Direction::LEFT:
            return (!isValidDirection(Direction::UP) &&
                    !isValidDirection(Direction::DOWN) &&
                    !isValidDirection(Direction::RIGHT));
        case Direction::RIGHT:
            return (!isValidDirection(Direction::UP) &&
                    !isValidDirection(Direction::DOWN) &&
                    !isValidDirection(Direction::LEFT));
        case Direction::NONE:
            return (!isValidDirection(Direction::UP) &&
                    !isValidDirection(Direction::DOWN) &&
                    !isValidDirection(Direction::LEFT) &&
                    !isValidDirection(Direction::RIGHT));
        default:
            throw std::logic_error("direction not handled");
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
