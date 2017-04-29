#include <cmath>
#include "Player.h"
#include "../../Config.h"
#include "../Game.h"

Player::Player(const double posX, const double posY, Game *game)
        : MovableObject(posX, posY, Config::PLAYER_BASE_SPEED, game),
          requestedDirection(Direction::NONE)
{

}

void Player::performActions()
{
    navigate();
    move();
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
    if (validDirection(requestedDirection))
    {
        direction = requestedDirection;
    } else if (!validDirection(direction))
    {
        direction = Direction::NONE;
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
