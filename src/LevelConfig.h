#ifndef PACMAN_USERCONFIG_H
#define PACMAN_USERCONFIG_H


#include "Difficulty.h"
#include <string>

/**
 * @brief Stores the user configuration passed as program arguments
 */
class UserConfig
{
public:
    UserConfig();

    const std::string &getMapFileName() const;

    void setMapFileName(const std::string &mapFileName);

    const Difficulty::Level getDifficultyLevel() const;

    /**
     * @brief Parses the user specified difficulty into the actual Difficulty::Level
     * @param levelStr
     * @throws Utils::ExceptionMessage on invalid (user) input
     */
    void setDifficultyLevel(const std::string levelStr);

private:
    std::string mapFileName;

    Difficulty::Level difficultyLevel;

};


#endif //PACMAN_USERCONFIG_H
