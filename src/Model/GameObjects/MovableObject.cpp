#include <cmath>
#include "MovableObject.h"
#include "../../Config.h"
#include "../Game.h"
#include "../../Utils.h"

MovableObject::MovableObject(const double posX, const double posY, const double speed, Game *game)
        : GameObject(posX, posY, game),
          baseSpeed(speed),
          speed(speed),
          direction(Direction::NONE)
{

}

void MovableObject::performActions()
{
    navigate();
    move();
}

void MovableObject::move()
{
    double currentStepSize = stepSize(speed);

    if (direction == Direction::UP)
    {
        posY = nextGridPosition(posY, -1 * currentStepSize);
    } else if (direction == Direction::DOWN)
    {
        posY = nextGridPosition(posY, currentStepSize);
    } else if (direction == Direction::LEFT)
    {
        posX = nextGridPosition(posX, -1 * currentStepSize);
    } else if (direction == Direction::RIGHT)
    {
        posX = nextGridPosition(posX, currentStepSize);
    }
}

const bool MovableObject::validDirection(const Direction direction) const
{
    uint16_t destSquarePosX = static_cast<uint16_t>(posX);
    uint16_t destSquarePosY = static_cast<uint16_t>(posY);

    switch (direction)
    {
        case Direction::UP:
            destSquarePosY -= 1;
            break;
        case Direction::DOWN:
            destSquarePosY += 1;
            break;
        case Direction::LEFT:
            destSquarePosX -= 1;
            break;
        case Direction::RIGHT:
            destSquarePosX += 1;
            break;
        default:
            break;
    }

    if (game->getMap().getSquareType(destSquarePosX, destSquarePosY) != SquareType::Wall)
    {
        return true;
    } else
    {
        return false;
    }
}

const double MovableObject::stepSize(const double speed) const
{
    return (speed * Config::CYCLE_TIME_MSECS) / 1000;
}

const bool MovableObject::isOnGrid() const
{
    return (Utils::decimalPart(posX) == 0 && Utils::decimalPart(posY) == 0);
}

const double MovableObject::nextGridPosition(const double position, const double step) const
{
    if (step >= 0)
    {
        if (!isOnGrid() && (Utils::decimalPart(position + step) < Utils::decimalPart(position)))
        {
            return std::ceil(position);
        } else {
            return position + step;
        }
    } else
    {
        if (!isOnGrid() && (Utils::decimalPart(position + step) > Utils::decimalPart(position)))
        {
            return std::floor(position);
        } else {
            return position + step;
        }
    }
}

const bool MovableObject::isHorizontalDirection(const Direction direction) const
{
    return (direction == Direction::LEFT || direction == Direction::RIGHT);
}

const bool MovableObject::isVerticalDirection(const Direction direction) const
{
    return (direction == Direction::UP || direction == Direction::DOWN);
}
