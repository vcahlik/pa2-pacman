#include "AggressiveGhost.h"
#include "../../../../Config.h"

AggressiveGhost::AggressiveGhost(Game *game)
    : Ghost(Config::GHOST_BASE_SPEED, NavigatorType::Bfs, Config::GHOST_AGGRESSIVE_COLOR, game)
{

}
