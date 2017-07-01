#include "FreakGhost.h"
#include "Model/Game.h"
#include "Config.h"
#include "Utils.h"

FreakGhost::FreakGhost(Game *game)
        : Ghost(game->getDifficulty().getGhostBaseSpeed(), NavigatorType::Random, Config::GHOST_FREAK_COLOR, game) {

}

void FreakGhost::chooseDirection() {
    if (!position.isOnCoordinateGrid()) {
        return;
    }

    if (!isValidDirection(direction) || game->getMap().isIntersectionForObject(position.toCoord(), *this)) {
        direction = getNavigator().navigate(game->getPlayer());

        configureSpeed();
    }
}

void FreakGhost::configureSpeed() {
    if (getState() != State::Chase) {
        // Can speed only in chase mode
        freakSpeed = false;
        return;
    }

    if (freakSpeed && (Utils::getRandom(Config::GHOST_FREAK_FAST_MODE_DISABLE_RANDOM_PERIOD) == 0)) {
        // Set default speed
        speed = baseSpeed;
        freakSpeed = false;
        return;
    }

    if (Utils::getRandom(Config::GHOST_FREAK_FAST_MODE_ENABLE_RANDOM_PERIOD) == 0) {
        // Start speeding
        freakSpeed = true;
        speed = baseSpeed * 3;
    }
}
