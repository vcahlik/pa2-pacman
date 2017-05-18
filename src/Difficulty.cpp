#include <stdexcept>
#include "Difficulty.h"
#include "Config.h"

Difficulty::Difficulty(const Level level)
{
    ghostBaseSpeed = Config::PLAYER_BASE_SPEED;
    ghostFrightenedDurationMsecs = Config::GHOST_FRIGHTENED_DEFAULT_DURATION_MSECS;

    switch (level)
    {
        case Level::Level1:
            ghostBaseSpeed *= 0.6;
            ghostFrightenedDurationMsecs *= 2;
            initialRemainingLives = 4;
            break;
        case Level::Level2:
            ghostBaseSpeed *= 0.7;
            ghostFrightenedDurationMsecs *= 1.5;
            initialRemainingLives = 3;
            break;
        case Level::Level3:
            ghostBaseSpeed *= 0.8;
            ghostFrightenedDurationMsecs *= 1;
            initialRemainingLives = 2;
            break;
        case Level::Level4:
            ghostBaseSpeed *= 0.9;
            ghostFrightenedDurationMsecs *= 0.8;
            initialRemainingLives = 1;
            break;
        case Level::Level5:
            ghostBaseSpeed *= 1;
            ghostFrightenedDurationMsecs *= 0.5;
            initialRemainingLives = 0;
            break;
        default:
            throw std::logic_error("level not handled");
    }
}

const double Difficulty::getGhostBaseSpeed() const
{
    return ghostBaseSpeed;
}

const uint32_t Difficulty::getGhostFrightenedDurationMsecs() const
{
    return ghostFrightenedDurationMsecs;
}

const uint32_t Difficulty::getInitialRemainingLives() const
{
    return initialRemainingLives;
}
