#include "Item.h"
#include "../../Game.h"

Item::Item(const Position position, const double size, Game *game)
        : GameObject(position, size, game),
          state(State::Placed)
{

}

void Item::performActions()
{
    if (isCollision(game->getPlayer()))
    {
        state = State::Removed;
    }
}

const Item::State Item::getState() const
{
    return state;
}
