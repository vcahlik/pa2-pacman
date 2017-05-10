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

    const Difficulty getDifficulty() const;

    void setDifficulty(Difficulty difficulty);

private:
    std::string mapFileName;

    Difficulty difficulty;

};


#endif //PACMAN_USERCONFIG_H
