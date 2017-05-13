#include "GameObject.h"

GameObject::GameObject(const double posX, const double posY, const double size, Game *game)
    : game(game),
      posX(0), posY(0),
      size(size)
{
    this->posX = getCenteredPos(posX);
    this->posY = getCenteredPos(posY);
}

const double GameObject::getPosX() const
{
    return posX;
}

const double GameObject::getPosY() const
{
    return posY;
}

const double GameObject::getSize() const
{
    return size;
}

const double GameObject::getCenteredPos(const double squarePos)
{
    return squarePos + (1 - size) / 2;
}
