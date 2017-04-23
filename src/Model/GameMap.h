#ifndef PACMAN_GAMEMAP_H
#define PACMAN_GAMEMAP_H

#include <string>
#include <vector>

class GameMap
{
public:
    enum class SquareType
    {
        Wall,
        Space,
        StartPos,
        SpawnPoint
    };

    GameMap(const std::string &filename);

    void loadFromFile(const std::string &filename);

    const bool positionInsideWall(const uint16_t posX, const uint16_t posY);

private:
    uint16_t sizeX;
    uint16_t sizeY;

    std::vector<std::vector<SquareType>> squares;

    SquareType symbolToSquareType(const char symbol);
};


#endif //PACMAN_GAMEMAP_H
