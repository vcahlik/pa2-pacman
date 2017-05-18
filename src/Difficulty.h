#ifndef PACMAN_DIFFICULTY_H
#define PACMAN_DIFFICULTY_H


#include <cstdint>

class Difficulty
{
public:
    enum class Level
    {
        Level1,
        Level2,
        Level3,
        Level4,
        Level5
    };

    Difficulty(const Level level);

    const double getGhostBaseSpeed() const;

    const uint32_t getGhostFrightenedDurationMsecs() const;

    const uint32_t getInitialRemainingLives() const;

private:
    double ghostBaseSpeed;
    uint32_t ghostFrightenedDurationMsecs;
    uint32_t initialRemainingLives;
};


#endif //PACMAN_DIFFICULTY_H
