#include "GameObject.h"

GameObject::GameObject(const double posX, const double posY, Game *game)
    : game(game),
      posX(posX), posY(posY)
{

}

void GameObject::performActions()
{

}

const double GameObject::getPosX() const
{
    return posX;
}

const double GameObject::getPosY() const
{
    return posY;
}
