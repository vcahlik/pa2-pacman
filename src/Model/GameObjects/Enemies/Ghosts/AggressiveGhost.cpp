#include "AggressiveGhost.h"
#include "Config.h"
#include "Model/Game.h"

AggressiveGhost::AggressiveGhost(Game *game)
        : Ghost(game->getDifficulty().getGhostBaseSpeed(), NavigatorType::Bfs, Config::GHOST_AGGRESSIVE_COLOR, game) {

}
