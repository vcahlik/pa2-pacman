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
        navigateAtIntersection();
    }
}

void Player::navigateAtIntersection()
{
    // Movement enabled by default
    speed = baseSpeed;

    if (isValidDirection(requestedDirection)) // Player can go where he wanted
    {
        direction = requestedDirection;
    } else if (!isValidDirection(direction)) // Player can't go where he wanted, but can't continue either
    {
        speed = 0;
        direction = requestedDirection; // Player can rotate
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

void Player::setAlive(const bool alive)
{
    this->alive = alive;
}
