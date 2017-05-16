#include "Ghost.h"
#include "../../../Config.h"
#include "../../Game.h"
#include "../../../Utils.h"

Ghost::Ghost(const Position position, const double speed, Game *game)
    : Enemy(position, speed, Config::GHOST_SIZE, NavigatorType::Random, game),
      color(getRandomColor())
{
    direction = getRandomValidDirection();
}

const Color Ghost::getColor() const
{
    return color;
}

const Color Ghost::getRandomColor() const
{
    switch (Utils::getRandom(5))
    {
        case 0:
            return Color::White;
        case 1:
            return Color::Green;
        case 2:
            return Color::Red;
        case 3:
            return Color::Magenta;
        default:
            return Color::Cyan;
    }
}
