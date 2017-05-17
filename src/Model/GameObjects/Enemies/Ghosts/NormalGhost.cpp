#include "NormalGhost.h"
#include "../../../../Config.h"

NormalGhost::NormalGhost(Game *game)
    : Ghost(Config::GHOST_BASE_SPEED, NavigatorType::Random, Config::GHOST_NORMAL_COLOR, game)
{

}
