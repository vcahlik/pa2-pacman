#include "AggressiveGhost.h"

AggressiveGhost::AggressiveGhost(const Position &position, const double speed, Game *game)
    : Ghost(position, speed, NavigatorType::BfsNavigator, Color::Red, game)
{

}
