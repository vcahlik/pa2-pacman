#include <cstdlib>
#include <stdexcept>
#include "Enemy.h"

Enemy::Enemy(const double posX, const double posY, const double speed, const double size, Game *game)
        : MovableObject(posX, posY, speed, size, game)
{

}

void Enemy::chooseRandomDirection()
{
    while (true)
    {
        int32_t random = abs(rand()) % 4;
        switch (random)
        {
            case 0:
                direction = Direction::UP;
                break;
            case 1:
                direction = Direction::DOWN;
                break;
            case 2:
                direction = Direction::LEFT;
                break;
            case 3:
                direction = Direction::RIGHT;
                break;
            default:
                throw std::logic_error("random range: incorrect implementation");
        }

        if (isValidDirection(direction))
        {
            break;
        }
    }
}
