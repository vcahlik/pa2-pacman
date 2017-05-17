#ifndef PACMAN_GHOST_H
#define PACMAN_GHOST_H


#include "../Enemy.h"
#include "../../../../View/Ncurses/Color.h"

class Ghost
    : public Enemy
{
public:
    enum class State
    {
        Chase,
        Frightened,
        InGhostHouse
    };

    explicit Ghost(const Position position, const double speed, const NavigatorType navigatorType, const Color color, Game *game);

    const State getState() const;

    const Color getColor() const;

private:
    const Color getRandomColor() const;

    const State state;

    const NavigatorType defaultNavigatorType;

    const Color color;

};


#endif //PACMAN_GHOST_H
