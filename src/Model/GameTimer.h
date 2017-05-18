#ifndef PACMAN_GAMETIMER_H
#define PACMAN_GAMETIMER_H


#include <map>

enum class Timeout
{
    GameStateGameWon,
    GameStateLifeLost,
    GameStateGameOver,
    GhostGeneration,
    CherryLifetime,
    CherryGeneration,
    GhostStateFrightened,
    GhostStateFrightenedEnd,
    GhostStateFrightenedBlink
};

class Game;

class GameTimer
{
public:
    GameTimer(const Game *game);

    void requestTimer(const Timeout timeout);

    void stopTimer(const Timeout timeout);

    const bool isTimeoutEvent(const Timeout timeout);

    void notifyOfNextCycle();

    const bool isActive(const Timeout timeout) const;

private:
    const bool timeoutExceeded(const Timeout timeout) const;

    const uint32_t getTimeoutLimitValue(const Timeout timeout) const;

    std::map<Timeout, uint32_t> timeoutsCounter;

    const Game *game;

};


#endif //PACMAN_GAMETIMER_H
