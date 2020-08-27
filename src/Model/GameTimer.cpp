#include "GameTimer.h"
#include "Config.h"
#include "Game.h"
#include <stdexcept>

GameTimer::GameTimer(const Game *game)
        : game(game) {}

void GameTimer::requestTimer(const TimeoutEvent timeout) {
    if (isActive(timeout)) {
        return;
    }

    timeoutsCounter[timeout] = 0;
}

void GameTimer::stopTimer(const TimeoutEvent timeout) {
    timeoutsCounter.erase(timeout);
}

const bool GameTimer::isTimeoutEvent(const TimeoutEvent timeout) {
    if (timeoutExceeded(timeout)) {
        stopTimer(timeout);
        return true;
    }

    return false;
}

void GameTimer::notifyOfNextCycle() {
    for (auto &a : timeoutsCounter) {
        if (!timeoutExceeded(a.first)) {
            a.second += Config::CYCLE_TIME_MSECS;
        }
    }
}

const bool GameTimer::isActive(const TimeoutEvent timeout) const {
    return timeoutsCounter.find(timeout) != timeoutsCounter.end();
}

const bool GameTimer::timeoutExceeded(const TimeoutEvent timeout) const {
    try {
        return timeoutsCounter.at(timeout) >= getTimeoutLimitValueMsecs(timeout);
    } catch (const std::out_of_range &) {
        return false;
    }
}

const uint32_t GameTimer::getTimeoutLimitValueMsecs(const TimeoutEvent timeout) const {
    switch (timeout) {
        case TimeoutEvent::GameStateGameWon:
            return Config::PLAYER_VICTORY_SCREEN_TIME_MSECS;
        case TimeoutEvent::GameStateLifeLost:
            return Config::PLAYER_DEATH_SCREEN_TIME_MSECS;
        case TimeoutEvent::GameStateGameOver:
            return Config::PLAYER_GAME_OVER_SCREEN_TIME_MSECS;
        case TimeoutEvent::GhostGeneration:
            return Config::GHOST_GENERATION_TIME_MSECS;
        case TimeoutEvent::CherryGeneration:
            return Config::CHERRY_GENERATION_INTERVAL_MSECS;
        case TimeoutEvent::CherryLifetime:
            return Config::CHERRY_LIFETIME_MSECS;
        case TimeoutEvent::GhostStateFrightened:
            return game->getDifficulty().getGhostFrightenedDurationMsecs();
        case TimeoutEvent::GhostStateFrightenedEnd:
            return Config::GHOST_FRIGHTENED_END_DURATION_MSECS;
        case TimeoutEvent::GhostStateFrightenedBlink:
            return Config::GHOST_FRIGHTENED_BLINK_INTERVAL_MSECS;
        default:
            throw std::logic_error("timeout not handled");
    }
}
