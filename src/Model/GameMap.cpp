#include "GameMap.h"
#include "../Config.h"
#include <fstream>
#include "GameObjects/MovableObject.h"

GameMap::GameMap(const std::string &filename)
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

            SquareType type = symbolToSquareType(c);
            lineSquares.push_back(type);

            switch (type)
            {
                case SquareType::StartPos:
                    startPosX = x;
                    startPosY = y;
                    break;
                case SquareType::SpawnPoint:
                    spawnPointX = x;
                    spawnPointY = y;
                    break;
                default:
                    break;
            }
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

const SquareType GameMap::symbolToSquareType(const char symbol) const
{
    switch (symbol)
    {
        case Config::MAP_FILE_SYMBOL_WALL:
            return SquareType::Wall;
        case Config::MAP_FILE_SYMBOL_SPACE:
            return SquareType::Space;
        case Config::MAP_FILE_SYMBOL_STARTPOS:
            return SquareType::StartPos;
        case Config::MAP_FILE_SYMBOL_SPAWNPOINT:
            return SquareType::SpawnPoint;
        default:
            throw std::runtime_error("Unknown square type");
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
    return startPosX;
}

const uint32_t GameMap::getStartPosY() const
{
    return startPosY;
}

const uint32_t GameMap::getSpawnPointX() const
{
    return spawnPointX;
}

const uint32_t GameMap::getSpawnPointY() const
{
    return spawnPointY;
}
