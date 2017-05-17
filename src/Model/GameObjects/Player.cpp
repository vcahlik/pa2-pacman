#include "Player.h"
#include "../../Config.h"
#include "../Game.h"

Player::Player(const Position position, Game *game)
        : MovableObject(position, Config::PLAYER_BASE_SPEED, Config::PLAYER_SIZE, game),
          requestedDirection(Direction::NONE),
          alive(true),
          mouthOpen(true), mouthOpenMsecs(0)
{

}

void Player::performActions()
{
    animateMouth();
    chooseDirection();
    move();
}

void Player::setMasterDirection(const Direction newDirection)
{
    direction = newDirection;
    requestedDirection = newDirection;
}

void Player::chooseDirection()
{
    if (requestedDirection == Direction::NONE)
    {
        direction = requestedDirection;
        return;
    }

    if (!position.isOnCoordinateGrid())
    {
        if (isHorizontalDirection(requestedDirection) == isHorizontalDirection(direction) ||
            isVerticalDirection(requestedDirection) == isVerticalDirection(direction))
        {
            direction = requestedDirection;
        }
    } else
    {
        navigateAtGridPosition();
    }
}

void Player::navigateAtGridPosition()
{
    // Movement enabled by default
    speed = baseSpeed;

    if (game->getMap().getSquareType(position.toCoord()) == SquareType::Teleport)
    {
        teleport();
        return;
    }

    if (isValidDirection(requestedDirection)) // Player can go where he wanted
    {
        direction = requestedDirection;
    } else if (!isValidDirection(direction)) // Player can't go where he wanted, but can't continue either
    {
        speed = 0;
        direction = requestedDirection; // Player can rotate
    }
}

void Player::teleport()
{
    position = game->getMap().getOtherTeleportEndCoordinates(position.toCoord());

    if (!isValidDirection(direction)) {
        setMasterDirection(getRandomValidDirection());
    }
}

void Player::requestGoUp()
{
    requestedDirection = Direction::UP;
}

void Player::requestGoDown()
{
    requestedDirection = Direction::DOWN;
}

void Player::requestGoLeft()
{
    requestedDirection = Direction::LEFT;
}

void Player::requestGoRight()
{
    requestedDirection = Direction::RIGHT;
}

const bool Player::isCompatibleSquareType(const SquareType squareType) const
{
    return (MovableObject::isCompatibleSquareType(squareType) ||
            squareType == SquareType::Teleport);
}

const bool Player::isMouthOpen() const
{
    return mouthOpen;
}

void Player::animateMouth()
{
    mouthOpenMsecs += Config::CYCLE_TIME_MSECS;
    if (mouthOpenMsecs >= Config::PLAYER_MOUTH_PERIOD_MSECS)
    {
        mouthOpen = !mouthOpen;
        mouthOpenMsecs = 0;
    }
}

const bool Player::isAlive() const
{
    return alive;
}

void Player::die()
{
    alive = false;
}
