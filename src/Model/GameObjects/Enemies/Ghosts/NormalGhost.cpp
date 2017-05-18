#include "NormalGhost.h"
#include "../../../../Config.h"
#include "../../../Game.h"

NormalGhost::NormalGhost(Game *game)
    : Ghost(game->getDifficulty().getGhostBaseSpeed(), NavigatorType::Random, Config::GHOST_NORMAL_COLOR, game)
{

}
