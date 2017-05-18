#include <cmath>
#include "MovableObject.h"
#include "../../Config.h"
#include "../Game.h"
#include "../../Utils.h"

MovableObject::MovableObject(const Position position, const double speed, const double size, Game *game)
        : GameObject(position, size, game),
          baseSpeed(speed),
          speed(speed),
          direction(Direction::NONE)
{

}

void MovableObject::performActions()
{
    chooseDirection();
    move();
}

const Direction MovableObject::getDirection() const
{
    return direction;
}

void MovableObject::move()
{
    Position nextPosition = position.relative(direction, stepSize(speed));

    if (position.isOnCoordinateGrid() ||
        nextPosition.toCoord() == position.toCoord())
    {
        // Not crossing coordinate grid
        position = nextPosition;
    } else
    {
        // Move would cross the coordinate grid, so we align position to grid

        if (direction == Direction::DOWN || direction == Direction::RIGHT)
        {
            position = nextPosition.toCoord();
        } else
        {
            position = position.toCoord();
        }
    }
}

const bool MovableObject::isValidDirection(const Direction direction) const
{
    try {
        return (isCompatibleSquareType(game->getMap().getSquareType(position.toCoord().relative(direction))));
    } catch (const std::out_of_range &)
    {
        return false;
    }
}

const double MovableObject::stepSize(const double speed) const
{
    return (speed * Config::CYCLE_TIME_MSECS) / 1000;
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

const Direction MovableObject::getRandomDifferentValidDirection(const Direction usedDirection) const
{
    if (isValidDirection(usedDirection) && isOnlyValidDirection(usedDirection))
    {
        return usedDirection;
    }

    while (true)
    {
        Direction newDirection = getRandomValidDirection();

        if (newDirection != usedDirection)
        {
            return newDirection;
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