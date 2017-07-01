#include <stdexcept>
#include "LevelConfig.h"
#include "Config.h"
#include "Utils.h"

LevelConfig::LevelConfig()
        : mapFileName(""), difficultyLevel(Config::DEFAULT_DIFFICULTY_LEVEL) {}

const std::string &LevelConfig::getMapFileName() const {
    return mapFileName;
}

void LevelConfig::setMapFileName(const std::string &mapFileName) {
    this->mapFileName = mapFileName;
}

const Difficulty::Level LevelConfig::getDifficultyLevel() const {
    return difficultyLevel;
}

void LevelConfig::setDifficultyLevel(const std::string difficultyLevelStr) {
    int32_t levelNumber = 0;

    try {
        levelNumber = std::stoi(difficultyLevelStr);
    } catch (const std::exception &) {
        throw Utils::ExceptionMessage("Difficulties: 1 2 3 4 5");
    }

    switch (levelNumber) {
        case 1:
            difficultyLevel = Difficulty::Level::Level1;
            break;
        case 2:
            difficultyLevel = Difficulty::Level::Level2;
            break;
        case 3:
            difficultyLevel = Difficulty::Level::Level3;
            break;
        case 4:
            difficultyLevel = Difficulty::Level::Level4;
            break;
        case 5:
            difficultyLevel = Difficulty::Level::Level5;
            break;
        default:
            throw Utils::ExceptionMessage("Difficulties: 1 2 3 4 5");
    }
}
