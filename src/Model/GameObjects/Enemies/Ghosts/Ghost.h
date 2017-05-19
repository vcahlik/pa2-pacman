#ifndef PACMAN_GHOST_H
#define PACMAN_GHOST_H


#include "../Enemy.h"
#include "../../../../View/Ncurses/Color.h"
#include "../../../GameTimer.h"

/**
 * @brief A classical enemy which is either chasing the player, frightened, or in the ghost house
 */
class Ghost
    : public Enemy
{
public:
    enum class State
    {
        Chase,
        Frightened, // Ghost can be eaten
        FrightenedEnd, // Indicates nearing return to chase
        InGhostHouse
    };

    explicit Ghost(const double speed, const NavigatorType navigatorType, const Color color, Game *game);

    void performActions() override;

    const State getState() const;

    void reset();

    /**
     * @brief Spawns the ghost
     * @throws std::runtime_error if ghost not in ghost house
     */
    void releaseFromGhostHouse();

    /**
     * @brief Attempts to frighten the ghost, not effective when in ghost house
     */
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
