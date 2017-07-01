#ifndef PACMAN_USERCONFIG_H
#define PACMAN_USERCONFIG_H


#include "Difficulty.h"
#include <string>

/**
 * @brief Stores the level's configuration
 */
class LevelConfig
{
public:
    LevelConfig();

    const std::string &getMapFileName() const;

    void setMapFileName(const std::string &mapFileName);

    const Difficulty::Level getDifficultyLevel() const;

    /**
     * @brief Parses the user specified difficulty into the actual Difficulty::Level
     * @param difficultyLevelStr
     * @throws Utils::ExceptionMessage on invalid (user) input
     */
    void setDifficultyLevel(const std::string difficultyLevelStr);

private:
    std::string mapFileName;

    Difficulty::Level difficultyLevel;

};


#endif //PACMAN_USERCONFIG_H
