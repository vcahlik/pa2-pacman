#include "Player.h"
#include "../../Config.h"
#include "../Game.h"

Player::Player(const double posX, const double posY, Game *game)
        : MovableObject(posX, posY, Config::PLAYER_BASE_SPEED, Config::PLAYER_SIZE, game),
          requestedDirection(Direction::NONE),
          alive(true),
          mouthOpen(true), mouthOpenMsecs(0)
{

}

const bool Player::performActions()
{
    animateMouth();
    navigate();
    move();

    return true;
}

void Player::changeDirection(const Direction newDirection)
{
    direction = newDirection;
    requestedDirection = newDirection;
}

void Player::navigate()
{
    if (requestedDirection == Direction::NONE)
    {
        direction = requestedDirection;
        return;
    }

    if (!isOnGrid())
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

    if (game->getMap().getSquareType(static_cast<uint32_t>(posX), static_cast<uint32_t>(posY)) == SquareType::Teleport)
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
    uint32_t destPosX = game->getMap().getOtherTeleportEndPosX(static_cast<uint32_t>(posX), static_cast<uint32_t>(posY));
    uint32_t destPosY = game->getMap().getOtherTeleportEndPosY(static_cast<uint32_t>(posX), static_cast<uint32_t>(posY));

    posX = destPosX;
    posY = destPosY;

    if (!isValidDirection(direction)) {
        changeDirection(getRandomValidDirection());
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

const bool Player::isEnterableSquareType(const SquareType squareType) const
{
    return (MovableObject::isEnterableSquareType(squareType) ||
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
