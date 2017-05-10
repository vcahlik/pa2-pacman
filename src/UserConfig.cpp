#include "UserConfig.h"
#include "Config.h"

UserConfig::UserConfig()
    : mapFileName(""), difficulty(Config::DEFAULT_DIFFICULTY)
{}

const std::string &UserConfig::getMapFileName() const
{
    return mapFileName;
}

void UserConfig::setMapFileName(const std::string &mapFileName)
{
    this->mapFileName = mapFileName;
}

const Difficulty UserConfig::getDifficulty() const
{
    return difficulty;
}

void UserConfig::setDifficulty(Difficulty difficulty)
{
    this->difficulty = difficulty;
}
