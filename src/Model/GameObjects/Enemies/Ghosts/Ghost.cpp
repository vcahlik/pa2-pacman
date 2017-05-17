#include "Ghost.h"
#include "../../../../Config.h"
#include "../../../Game.h"
#include "../../../../Utils.h"

Ghost::Ghost(const Position position, const double speed, const NavigatorType defaultNavigatorType, const Color color, Game *game)
    : Enemy(position, speed, Config::GHOST_SIZE, defaultNavigatorType, game),
      state(State::InGhostHouse),
      defaultNavigatorType(defaultNavigatorType),
      color(color)
{
    direction = getRandomValidDirection();
}

const Ghost::State Ghost::getState() const
{
    return state;
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
