#include "GameMap.h"
#include "Config.h"
#include <fstream>

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

    uint16_t parsingSizeX = line.length();

    for (uint16_t row = 1; true; ++row)
    {
        std::vector<SquareType> lineSquares;
        for (const char &c : line)
        {
            lineSquares.push_back(symbolToSquareType(c));
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

    // TODO map perimeter must be walls

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

const uint16_t GameMap::sizeX() const
{
    if (squares.empty())
    {
        return 0;
    }

    return squares[0].size();
}

const uint16_t GameMap::sizeY() const
{
    return squares.size();
}

const SquareType GameMap::getSquareType(const uint16_t posX, const uint16_t posY) const
{
    return squares[posY][posX];
}
