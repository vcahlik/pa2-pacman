#ifndef PACMAN_GAMETIMER_H
#define PACMAN_GAMETIMER_H


#include <map>

/**
 * @brief Representation of different timeout requests and events, so that they can be kept track of simultaneously
 */
enum class TimeoutEvent
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

/**
 * @brief Timer which keeps track of simultaneous Timeout events
 */
class GameTimer
{
public:
    GameTimer(const Game *game);

    /**
     * @brief Starts the timer for specified Timeout event if not already running
     * @param timeout
     */
    void requestTimer(const TimeoutEvent timeout);

    /**
     * @brief Discards the timer
     * @param timeout
     */
    void stopTimer(const TimeoutEvent timeout);

    /**
     * @brief Checks if TimeoutEvent has happened, if yes, timer is discarded and method will not report it again
     * @param timeout
     * @return true Timeout happened
     */
    const bool isTimeoutEvent(const TimeoutEvent timeout);

    /**
     * @brief Gives the timer the conception of time
     */
    void notifyOfNextCycle();

    /**
     * @brief Checks if timer is running, or if TimeoutEvent has happened but timer is not discarded yet
     * @param timeout
     * @return
     */
    const bool isActive(const TimeoutEvent timeout) const;

private:
    const bool timeoutExceeded(const TimeoutEvent timeout) const;

    /**
     * @brief Gets the timeout duration
     * @param timeout
     * @return
     * @throws std::logic_error on TimeoutEvent not handled
     */
    const uint32_t getTimeoutLimitValueMsecs(const TimeoutEvent timeout) const;

    std::map<TimeoutEvent, uint32_t> timeoutsCounter; /**< @brief Storage of timers for different TimeoutEvents */

    const Game *game;

};


#endif //PACMAN_GAMETIMER_H
