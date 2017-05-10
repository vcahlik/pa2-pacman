#include "GameTimer.h"
#include "../Config.h"

void GameTimer::requestTimer(const Timeout timeout)
{
    if (isActive(timeout))
    {
        return;
    }

    timeoutsCounter[timeout] = 0;
}
const bool GameTimer::isTimeoutEvent(const Timeout timeout)

{
    if (timeoutExceeded(timeout))
    {
        timeoutsCounter.erase(timeout);
        return true;
    }

    return false;
}

void GameTimer::notifyOfNextCycle()
{
    for (auto &a : timeoutsCounter)
    {
        if (!timeoutExceeded(a.first))
        {
            a.second += Config::CYCLE_TIME_MSECS;
        }
    }
}

const bool GameTimer::isActive(const Timeout timeout) const
{
    return timeoutsCounter.find(timeout) != timeoutsCounter.end();
}

const bool GameTimer::timeoutExceeded(const Timeout timeout) const
{
    try {
        return timeoutsCounter.at(timeout) >= getTimeoutLimitValue(timeout);
    } catch (std::out_of_range &)
    {
        return false;
    }
}

const uint32_t GameTimer::getTimeoutLimitValue(const Timeout timeout) const
{
    switch (timeout)
    {
        case Timeout::PlayerVictoryScreen:
            return Config::PLAYER_VICTORY_SCREEN_TIME_MSECS;
        case Timeout::PlayerDeathScreen:
            return Config::PLAYER_DEATH_SCREEN_TIME_MSECS;
        case Timeout::GameOverScreen:
            return Config::PLAYER_GAME_OVER_SCREEN_TIME_MSECS;
        case Timeout::GhostGeneration:
            return Config::GHOST_GENERATION_TIME_MSECS;
        default:
            throw std::logic_error("timeout not handled");
    }
}
