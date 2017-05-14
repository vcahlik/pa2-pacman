#include "Item.h"
#include "../../Game.h"

Item::Item(const Position position, const double size, Game *game)
        : GameObject(position, size, game)
{

}

const bool Item::performActions()
{
    if (isCollision(game->getPlayer()))
    {
        return false;
    }

    return true;
}
