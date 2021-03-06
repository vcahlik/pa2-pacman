#include "PowerUp.h"
#include "Config.h"
#include "Model/GameObjects/Enemies/Ghosts/Ghost.h"
#include "Model/Game.h"

PowerUp::PowerUp(const Position &position, Game *game)
        : Item(position, Config::POWERUP_SIZE, game) {

}

void PowerUp::performActions() {
    Item::performActions();

    if (state == State::Removed) {
        game->frightenGhosts();
    }
}
