#include "GameMap.h"
#include "Config.h"
#include <fstream>
#include "GameObjects/MovableObject.h"
#include "Utils.h"

GameMap::GameMap(const std::string &filename)
        : teleportSquaresCount(0),
          startPosSet(false),
          spawnPointSet(false) {
    loadFromFile(filename);
}

void GameMap::loadFromFile(const std::string &filename) {
    std::ifstream file;
    file.open(filename, std::ios::in);
    if (!file.is_open()) {
        throw Utils::ExceptionMessage("Error parsing map file: can not open file");
    }

    std::string line;
    std::getline(file, line);
    if (!file.good()) {
        file.close();
        throw Utils::ExceptionMessage("Error parsing map file: i/o error, possibly empty file");
    }

    uint32_t parsingSizeX = static_cast<uint32_t>(line.length());

    for (uint32_t y = 0; true; ++y) {
        std::vector<SquareType> lineSquares;
        for (uint32_t x = 0; x < line.length(); ++x) {
            char c = line[x];
            const Coordinates coord = Coordinates(x, y);

            MapFileSymbol symbol = charToMapFileSymbol(c);

            switch (symbol) {
                case MapFileSymbol::StartPos:
                    if (startPosSet) {
                        throw Utils::ExceptionMessage("Error parsing map file: multiple start positions");
                    }
                    startPosCoord = coord;
                    startPosSet = true;
                    break;
                case MapFileSymbol::SpawnPoint:
                    if (spawnPointSet) {
                        throw Utils::ExceptionMessage("Error parsing map file: multiple spawn points");
                    }
                    spawnPointCoord = coord;
                    spawnPointSet = true;
                    break;
                case MapFileSymbol::Teleport:
                    if (teleportSquaresCount == 0) {
                        teleportACoord = coord;
                        ++teleportSquaresCount;
                    } else if (teleportSquaresCount == 1) {
                        teleportBCoord = coord;
                        ++teleportSquaresCount;
                    } else {
                        throw Utils::ExceptionMessage("Error parsing map file: two teleports is maximum");
                    }
                    break;
                case MapFileSymbol::PowerUp:
                    powerUpLocations.insert(coord);
                    break;
                default:
                    break;
            }

            lineSquares.push_back(mapFileSymbolToSquareType(symbol));
        }

        squares.push_back(lineSquares);

        std::getline(file, line);
        if (!file.good()) {
            if (file.eof()) {
                break;
            } else {
                file.close();
                throw Utils::ExceptionMessage("Error parsing map file: i/o error");
            }
        }
        if (line.length() != parsingSizeX) {
            file.close();
            throw Utils::ExceptionMessage("Error parsing map file: map must be rectangular");
        }
    }

    checkIntegrity();

    file.close();
}

const GameMap::MapFileSymbol GameMap::charToMapFileSymbol(const char character) const {
    switch (character) {
        case Config::MAP_FILE_SYMBOL_WALL:
            return MapFileSymbol::Wall;
        case Config::MAP_FILE_SYMBOL_SPACE:
            return MapFileSymbol::Space;
        case Config::MAP_FILE_SYMBOL_STARTPOS:
            return MapFileSymbol::StartPos;
        case Config::MAP_FILE_SYMBOL_SPAWNPOINT:
            return MapFileSymbol::SpawnPoint;
        case Config::MAP_FILE_SYMBOL_TELEPORT:
            return MapFileSymbol::Teleport;
        case Config::MAP_FILE_SYMBOL_POWERUP:
            return MapFileSymbol::PowerUp;
        default:
            throw Utils::ExceptionMessage("Error parsing map file: unknown symbol");
    }
}

const SquareType GameMap::mapFileSymbolToSquareType(const MapFileSymbol mapFileSymbol) const {
    switch (mapFileSymbol) {
        case MapFileSymbol::StartPos:
        case MapFileSymbol::Space:
            return SquareType::Space;
        case MapFileSymbol::SpawnPoint:
            return SquareType::SpawnPoint;
        case MapFileSymbol::Wall:
            return SquareType::Wall;
        case MapFileSymbol::Teleport:
            return SquareType::Teleport;
        case MapFileSymbol::PowerUp:
            return SquareType::Space;
        default:
            throw std::logic_error("Map file symbol not handled");
    }
}

const uint32_t GameMap::getSizeX() const {
    if (squares.empty()) {
        return 0;
    }

    return static_cast<uint32_t>(squares[0].size());
}

const uint32_t GameMap::getSizeY() const {
    return static_cast<uint32_t>(squares.size());
}

const bool GameMap::isIntersectionForObject(const Coordinates coord, const MovableObject &object) const {
    if (!object.isCompatibleSquareType(getSquareType(coord))) {
        return false;
    }

    const bool upCompatible = object.isCompatibleSquareType(getSquareType(coord.relative(Direction::UP)));
    const bool downCompatible = object.isCompatibleSquareType(getSquareType(coord.relative(Direction::DOWN)));
    const bool leftCompatible = object.isCompatibleSquareType(getSquareType(coord.relative(Direction::LEFT)));
    const bool rightCompatible = object.isCompatibleSquareType(getSquareType(coord.relative(Direction::RIGHT)));

    return !(upCompatible == downCompatible &&
             leftCompatible == rightCompatible &&
             upCompatible != leftCompatible);
}

const Coordinates GameMap::getRandomCompatibleCoord(const GameObject &object) const {
    Coordinates candidateCoord;

    while (true) {
        candidateCoord.x = Utils::getRandom(getSizeX());
        candidateCoord.y = Utils::getRandom(getSizeY());
        if (object.isCompatibleSquareType(getSquareType(candidateCoord))) {
            return candidateCoord;
        }
    }
}

const SquareType GameMap::getSquareType(const Coordinates coord) const {
    return squares.at(coord.y).at(coord.x);
}

void GameMap::checkIntegrity() const {
    checkMapHasBorderWalls();

    if (!startPosSet) {
        throw Utils::ExceptionMessage("Error parsing map file: start position not set");
    }

    if (!spawnPointSet) {
        throw Utils::ExceptionMessage("Error parsing map file: spawn point not set");
    }

    if ((teleportSquaresCount != 0) &&
        (teleportSquaresCount != 2)) {
        throw Utils::ExceptionMessage("Error parsing map file: must include exactly two or zero teleports");
    }
}

void GameMap::checkMapHasBorderWalls() const {
    for (uint32_t y = 0; y < getSizeY(); ++y) {
        for (uint32_t x = 0; x < getSizeX(); ++x) {
            if (y == 0 || y == getSizeY() - 1 || x == 0 || x == getSizeX() - 1) {
                SquareType squareType = getSquareType(Coordinates(x, y));
                if ((squareType != SquareType::Wall) &&
                    (squareType != SquareType::Teleport)) {
                    throw Utils::ExceptionMessage(
                            "Error parsing map file: map mast have borders made of walls or teleports");
                }
            }
        }
    }
}

const bool GameMap::isCoordinatesWithinMap(const Coordinates coord) const {
    return coord.x >= 0 && coord.x < static_cast<int32_t>(getSizeX()) &&
           coord.y >= 0 && coord.y < static_cast<int32_t>(getSizeY());
}

const Coordinates GameMap::getStartPosCoordinates() const {
    return startPosCoord;
}

const Coordinates GameMap::getSpawnPointCoordinates() const {
    return spawnPointCoord;
}

const Coordinates GameMap::getOtherTeleportEndCoordinates(const Coordinates entryPosCoord) const {
    if (entryPosCoord == teleportACoord) {
        return teleportBCoord;
    } else if (entryPosCoord == teleportBCoord) {
        return teleportACoord;
    } else {
        throw Utils::ExceptionMessage("Error parsing map file: Input position is not a teleport");
    }
}

const std::set<Coordinates> GameMap::getPowerUpLocations() const {
    return powerUpLocations;
}
