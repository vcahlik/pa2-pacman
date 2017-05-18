#ifndef PACMAN_USERCONFIG_H
#define PACMAN_USERCONFIG_H


#include "Difficulty.h"
#include <string>

class UserConfig
{
public:
    UserConfig();

    const std::string &getMapFileName() const;

    void setMapFileName(const std::string &mapFileName);

    const Difficulty::Level getDifficultyLevel() const;

    void setDifficultyLevel(const std::string levelStr);

    uint32_t getInitialRemainingLives() const;

private:
    std::string mapFileName;

    Difficulty::Level difficultyLevel;

};


#endif //PACMAN_USERCONFIG_H
