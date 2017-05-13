#include "GameObject.h"

GameObject::GameObject(const double posX, const double posY, const double size, Game *game)
    : game(game),
      posX(calculateCenteredPos(posX, size)), posY(calculateCenteredPos(posY, size)),
      size(size)
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

const double GameObject::getSize() const
{
    return size;
}

const double GameObject::calculateCenteredPos(const double squarePos, const double objectSize)
{
    return squarePos + (1 - objectSize) / 2;
}
