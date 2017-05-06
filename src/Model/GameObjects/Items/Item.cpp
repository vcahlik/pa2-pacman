#include "Item.h"
#include "../../Game.h"

Item::Item(const double posX, const double posY, const double size, Game *game)
        : GameObject(posX, posY, size, game)
{

}

const bool Item::performActions()
{
    if (game->isObjectCollision(*this, game->getPlayer()))
    {
        return false;
    }

    return true;
}
