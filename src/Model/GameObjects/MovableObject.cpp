#include <cmath>
#include "MovableObject.h"
#include "../../Config.h"
#include "../Game.h"
#include "../../Utils.h"

MovableObject::MovableObject(const double posX, const double posY, const double speed, const double size, Game *game)
        : GameObject(posX, posY, size, game),
          baseSpeed(speed),
          speed(speed),
          direction(Direction::NONE)
{

}

const bool MovableObject::performActions()
{
    navigate();
    move();

    return true;
}

const Direction MovableObject::getDirection() const
{
    return direction;
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

const bool MovableObject::isValidDirection(const Direction direction) const
{
    uint32_t destSquarePosX = static_cast<uint32_t>(posX);
    uint32_t destSquarePosY = static_cast<uint32_t>(posY);

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

    // Check if position within map boundaries
    if (destSquarePosX < 0 || destSquarePosX >= game->getMap().sizeX() ||
        destSquarePosY < 0 || destSquarePosY >= game->getMap().sizeY())
    {
        return false;
    }

    try {
        return (isEnterableSquareType(game->getMap().getSquareType(destSquarePosX, destSquarePosY)));
    } catch (std::out_of_range &)
    {
        return false;
    }
}

const bool MovableObject::isEnterableSquareType(const SquareType squareType) const
{
    return squareType == SquareType::Space;
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

const bool MovableObject::noValidDirectionExists() const
{
    return (!isValidDirection(Direction::UP) &&
            !isValidDirection(Direction::DOWN) &&
            !isValidDirection(Direction::LEFT) &&
            !isValidDirection(Direction::RIGHT));
}

const Direction MovableObject::getRandomValidDirection() const
{
    if (noValidDirectionExists())
    {
        return Direction::NONE;
    }

    Direction candidateDirection;

    while (true)
    {
        switch (Utils::getRandom(4))
        {
            case 0:
                candidateDirection = Direction::UP;
                break;
            case 1:
                candidateDirection = Direction::DOWN;
                break;
            case 2:
                candidateDirection = Direction::LEFT;
                break;
            case 3:
                candidateDirection = Direction::RIGHT;
                break;
            default:
                throw std::logic_error("random range: incorrect implementation");
        }

        if (isValidDirection(candidateDirection))
        {
            return candidateDirection;
        }
    }
}

const bool MovableObject::isOnlyValidDirection(const Direction newDirection) const
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