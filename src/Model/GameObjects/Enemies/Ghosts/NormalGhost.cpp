#include "NormalGhost.h"
#include "Config.h"
#include "Model/Game.h"

NormalGhost::NormalGhost(Game *game)
        : Ghost(game->getDifficulty().getGhostBaseSpeed(), NavigatorType::Random, Config::GHOST_NORMAL_COLOR, game) {

}
