#ifndef PACMAN_DIFFICULTY_H
#define PACMAN_DIFFICULTY_H


#include <cstdint>

/**
 * @brief Stores game difficulity configurations for different levels
 */
class Difficulty
{
public:
    /**
     * @brief Difficulity levels, higher is more difficult
     */
    enum class Level
    {
        Level1,
        Level2,
        Level3,
        Level4,
        Level5
    };

    /**
     * @param level
     * @throws std::logic_error on unhandled Level
     */
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
