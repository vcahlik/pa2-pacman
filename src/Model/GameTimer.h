#ifndef PACMAN_GAMETIMER_H
#define PACMAN_GAMETIMER_H


#include <map>

enum class Timeout
{
    StateGameWon,
    StateLifeLost,
    StateGameOver,
    GhostGeneration
};

class GameTimer
{
public:
    void requestTimer(const Timeout timeout);

    const bool isTimeoutEvent(const Timeout timeout);

    void notifyOfNextCycle();

    const bool isActive(const Timeout timeout) const;

private:
    const bool timeoutExceeded(const Timeout timeout) const;

    const uint32_t getTimeoutLimitValue(const Timeout timeout) const;

    std::map<Timeout, uint32_t> timeoutsCounter;

};


#endif //PACMAN_GAMETIMER_H
