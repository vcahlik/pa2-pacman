#include "GameTimer.h"
#include "../Config.h"
#include "Game.h"

GameTimer::GameTimer(const Game *game)
    : game(game)
{}

void GameTimer::requestTimer(const Timeout timeout)
{
    if (isActive(timeout))
    {
        return;
    }

    timeoutsCounter[timeout] = 0;
}

void GameTimer::stopTimer(const Timeout timeout)
{
    timeoutsCounter.erase(timeout);
}

const bool GameTimer::isTimeoutEvent(const Timeout timeout)
{
    if (timeoutExceeded(timeout))
    {
        stopTimer(timeout);
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
    } catch (const std::out_of_range &)
    {
        return false;
    }
}

const uint32_t GameTimer::getTimeoutLimitValue(const Timeout timeout) const
{
    switch (timeout)
    {
        case Timeout::GameStateGameWon:
            return Config::PLAYER_VICTORY_SCREEN_TIME_MSECS;
        case Timeout::GameStateLifeLost:
            return Config::PLAYER_DEATH_SCREEN_TIME_MSECS;
        case Timeout::GameStateGameOver:
            return Config::PLAYER_GAME_OVER_SCREEN_TIME_MSECS;
        case Timeout::GhostGeneration:
            return Config::GHOST_GENERATION_TIME_MSECS;
        case Timeout::CherryGeneration:
            return Config::CHERRY_GENERATION_INTERVAL_MSECS;
        case Timeout::CherryLifetime:
            return Config::CHERRY_LIFETIME_MSECS;
        case Timeout::GhostStateFrightened:
            return game->getDifficulty().getGhostFrightenedDurationMsecs();
        case Timeout::GhostStateFrightenedEnd:
            return Config::GHOST_FRIGHTENED_END_DURATION_MSECS;
        case Timeout::GhostStateFrightenedBlink:
            return Config::GHOST_FRIGHTENED_BLINK_INTERVAL_MSECS;
        default:
            throw std::logic_error("timeout not handled");
    }
}
