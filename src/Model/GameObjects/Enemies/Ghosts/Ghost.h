#ifndef PACMAN_GHOST_H
#define PACMAN_GHOST_H


#include "../Enemy.h"
#include "../../../../View/Ncurses/Color.h"
#include "../../../GameTimer.h"

class Ghost
    : public Enemy
{
public:
    enum class State
    {
        Chase,
        Frightened,
        FrightenedEnd,
        InGhostHouse
    };

    explicit Ghost(const double speed, const NavigatorType navigatorType, const Color color, Game *game);

    void performActions() override;

    const State getState() const;

    void reset();

    void releaseFromGhostHouse();

    void frighten();

    const Color getColor() const;

protected:
    const double baseSpeed;

private:
    void performStateChaseActions();

    void performStateFrightenedActions();

    void performStateFrightenedEndActions();

    void setState(const State newState);

    void die();

    void switchToChaseState();

    void switchToFrightenedState();

    void switchToInGhostHouseState();

    State state;

    const NavigatorType defaultNavigatorType;

    const Color baseColor;

    GameTimer timer;

    bool frightenedBlinkOn;

};


#endif //PACMAN_GHOST_H
