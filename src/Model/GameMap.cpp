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
    uint16_t parsingSizeY = 0;

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
                parsingSizeY = row;
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

    sizeX = parsingSizeX;
    sizeY = parsingSizeY;

    file.close();
}

GameMap::SquareType GameMap::symbolToSquareType(const char symbol)
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
