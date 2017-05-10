#include "Ghost.h"
#include "../../../Config.h"
#include "../../Game.h"
#include "../../../Utils.h"

Ghost::Ghost(const double posX, const double posY, const double speed, Game *game)
    : Enemy(posX, posY, speed, Config::GHOST_SIZE, game),
      color(getRandomColor())
{
    chooseRandomDirection();
}

void Ghost::navigate()
{
    if (!isOnGrid())
    {
        return;
    }

    if (!isValidDirection(direction) || game->getMap().isIntersection(static_cast<uint32_t>(posX), static_cast<uint32_t>(posY)))
    {
        chooseRandomDirection();
    }
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
