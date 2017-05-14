#include "GameMap.h"
#include "../Config.h"
#include <fstream>
#include "GameObjects/MovableObject.h"
#include "../Utils.h"

GameMap::GameMap(const std::string &filename)
    : teleportSquaresCount(0)
{
    loadFromFile(filename);
}

void GameMap::loadFromFile(const std::string &filename)
{
    std::ifstream file;
    file.open(filename, std::ios::in);
    if (!file.is_open())
    {
        throw std::runtime_error("Could not open map file");
    }

    std::string line;
    std::getline(file, line);
    if (!file.good())
    {
        file.close();
        throw std::runtime_error("Error parsing map file");
    }

    uint32_t parsingSizeX = static_cast<uint32_t>(line.length());

    for (uint32_t y = 0; true; ++y)
    {
        std::vector<SquareType> lineSquares;
        for (uint32_t x = 0; x < line.length(); ++x)
        {
            char c = line[x];

            MapFileSymbol symbol = charToMapFileSymbol(c);

            switch (symbol)
            {
                case MapFileSymbol::StartPos:
                    startPosCoord = Coordinates(x, y);
                    break;
                case MapFileSymbol::SpawnPoint:
                    spawnPointCoord = Coordinates(x, y);
                    break;
                case MapFileSymbol::Teleport:
                    if (teleportSquaresCount == 0)
                    {
                        teleportACoord = Coordinates(x, y);
                        ++teleportSquaresCount;
                    } else if (teleportSquaresCount == 1)
                    {
                        teleportBCoord = Coordinates(x, y);
                        ++teleportSquaresCount;
                    } else {
                        throw std::runtime_error("Error parsing map file: wrong number of teleports");
                    }
                default:
                    break;
            }

            lineSquares.push_back(mapFileSymbolToSquareType(symbol));
        }

        squares.push_back(lineSquares);

        std::getline(file, line);
        if (!file.good())
        {
            if (file.eof())
            {
                break;
            } else
            {
                file.close();
                throw std::runtime_error("Error parsing map file");
            }
        }
        if (line.length() != parsingSizeX)
        {
            file.close();
            throw std::runtime_error("Error parsing map file: size mismatch");
        }
    }

    checkIntegrity();

    file.close();
}

const GameMap::MapFileSymbol GameMap::charToMapFileSymbol(const char character) const
{
    switch (character)
    {
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
        default:
            throw std::runtime_error("Unknown map file symbol");
    }
}

const SquareType GameMap::mapFileSymbolToSquareType(const MapFileSymbol mapFileSymbol) const
{
    switch (mapFileSymbol)
    {
        case MapFileSymbol::StartPos:
        case MapFileSymbol::Space:
            return SquareType::Space;
        case MapFileSymbol::SpawnPoint:
            return SquareType::SpawnPoint;
        case MapFileSymbol::Wall:
            return SquareType::Wall;
        case MapFileSymbol::Teleport:
            return SquareType::Teleport;
        default:
            throw std::logic_error("Map file symbol not handled");
    }
}

const uint32_t GameMap::sizeX() const
{
    if (squares.empty())
    {
        return 0;
    }

    return static_cast<uint32_t>(squares[0].size());
}

const uint32_t GameMap::sizeY() const
{
    return static_cast<uint32_t>(squares.size());
}

const bool GameMap::isIntersectionForObject(const Coordinates coord, const MovableObject &object) const
{
    if (!object.isCompatibleSquareType(getSquareType(coord)))
    {
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

const Coordinates GameMap::getRandomCompatibleCoord(const GameObject &object) const
{
    Coordinates candidateCoord;

    while (true)
    {
        candidateCoord.x = Utils::getRandom(sizeX());
        candidateCoord.y = Utils::getRandom(sizeY());
        if (object.isCompatibleSquareType(getSquareType(candidateCoord)))
        {
            return candidateCoord;
        }
    }
}

const SquareType GameMap::getSquareType(const Coordinates coord) const
{
    return squares.at(coord.y).at(coord.x);
}

void GameMap::checkIntegrity()
{
    // TODO
    // map must have borders
    // only one startPos and spawnPoint
    // two or zero teleports
}

const bool GameMap::coordinatesWithinMap(const Coordinates coord) const
{
    return coord.x >= 0 && coord.x < static_cast<int32_t>(sizeX()) &&
           coord.y >= 0 && coord.y < static_cast<int32_t>(sizeY());
}

const Coordinates GameMap::getStartPosCoordinates() const
{
    return startPosCoord;
}

const Coordinates GameMap::getSpawnPointCoordinates() const
{
    return spawnPointCoord;
}

const Coordinates GameMap::getOtherTeleportEndCoordinates(const Coordinates entryPosCoord) const
{
    if (entryPosCoord == teleportACoord)
    {
        return teleportBCoord;
    } else if (entryPosCoord == teleportBCoord)
    {
        return teleportACoord;
    } else {
        throw std::runtime_error("Input position is not a teleport");
    }
}
