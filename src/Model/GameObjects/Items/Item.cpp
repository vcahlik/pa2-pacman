#include "Item.h"
#include "Model/Game.h"

Item::Item(const Position position, const double size, Game *game)
        : GameObject(position, size, game),
          state(State::Placed) {

}

void Item::performActions() {
    if (isCollision(game->getPlayer())) {
        // Game will automatically remove the object
        state = State::Removed;
    }
}

const Item::State Item::getState() const {
    return state;
}
