#include "GameMap.h"
#include "../Config.h"
#include <fstream>
#include "GameObjects/MovableObject.h"

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
                    startPos = SquarePosition(x, y);
                    break;
                case MapFileSymbol::SpawnPoint:
                    spawnPointPos = SquarePosition(x, y);
                    break;
                case MapFileSymbol::Teleport:
                    if (teleportSquaresCount == 0)
                    {
                        teleportAPos = SquarePosition(x, y);
                        ++teleportSquaresCount;
                    } else if (teleportSquaresCount == 1)
                    {
                        teleportBPos = SquarePosition(x, y);
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

const bool GameMap::isIntersectionForObject(const uint32_t posX, const uint32_t posY, const MovableObject &object) const
{
    if (posX == 0 || posX >= sizeX() || posY == 0 || posY > sizeY())
    {
        throw std::logic_error("isIntersectionForObject(): called on border position");
    }

    if (object.isEnterableSquareType(getSquareType(posX, posY)))
    {
        if (object.isEnterableSquareType(getSquareType(posX - 1, posY)) &&
            object.isEnterableSquareType(getSquareType(posX + 1, posY)) &&
            !object.isEnterableSquareType(getSquareType(posX, posY - 1)) &&
            !object.isEnterableSquareType(getSquareType(posX, posY + 1)))
        {
            return false;
        } else if (!object.isEnterableSquareType(getSquareType(posX - 1, posY)) &&
                   !object.isEnterableSquareType(getSquareType(posX + 1, posY)) &&
                   object.isEnterableSquareType(getSquareType(posX, posY - 1)) &&
                   object.isEnterableSquareType(getSquareType(posX, posY + 1)))
        {
            return false;
        }
    }

    return true;
}

const SquareType GameMap::getSquareType(const uint32_t posX, const uint32_t posY) const
{
    return squares.at(posY).at(posX);
}

void GameMap::checkIntegrity()
{
    // TODO map must have borders, only one startPos and spawnPoint, ...
}

const uint32_t GameMap::getStartPosX() const
{
    return startPos.x;
}

const uint32_t GameMap::getStartPosY() const
{
    return startPos.y;
}

const uint32_t GameMap::getSpawnPointPosX() const
{
    return spawnPointPos.x;
}

const uint32_t GameMap::getSpawnPointPosY() const
{
    return spawnPointPos.y;
}

const uint32_t GameMap::getOtherTeleportEndPosX(const uint32_t entryPosX, const uint32_t entryPosY) const
{
    if (entryPosX == teleportAPos.x &&
        entryPosY == teleportAPos.y)
    {
        return teleportBPos.x;
    } else if (entryPosX == teleportBPos.x &&
               entryPosY == teleportBPos.y)
    {
        return teleportAPos.x;
    } else {
        throw std::runtime_error("Input position is not a teleport");
    }
}

const uint32_t GameMap::getOtherTeleportEndPosY(const uint32_t entryPosX, const uint32_t entryPosY) const
{
    if (entryPosX == teleportAPos.x &&
        entryPosY == teleportAPos.y)
    {
        return teleportBPos.y;
    } else if (entryPosX == teleportBPos.x &&
               entryPosY == teleportBPos.y)
    {
        return teleportAPos.y;
    } else {
        throw std::runtime_error("Input position is not a teleport");
    }
}

GameMap::SquarePosition::SquarePosition(const uint32_t x, const uint32_t y)
        : x(x), y(y)
{}

GameMap::SquarePosition::SquarePosition()
        : x(0), y(0)
{}