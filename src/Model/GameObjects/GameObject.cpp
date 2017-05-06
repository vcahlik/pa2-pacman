#include "GameObject.h"

GameObject::GameObject(const double posX, const double posY, const double size, Game *game)
    : game(game),
      posX(posX + (1-size)/2), posY(posY + (1-size)/2),
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
