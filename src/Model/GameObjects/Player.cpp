#include "Player.h"
#include "../../Config.h"
#include "../Game.h"

Player::Player(const double posX, const double posY, Game *game)
        : MovableObject(posX, posY, Config::PLAYER_BASE_SPEED, game)
{

}

void Player::performActions()
{
    GameObject::performActions();

    if (game->getMap().getSquareType(posX, posY) == SquareType::Space)
    {
        posX += 0.0005;
    }
    else
    {
        posY -= 0.0005;
    }
}
