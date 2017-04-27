#ifndef PACMAN_GAMEMAP_H
#define PACMAN_GAMEMAP_H

#include <string>
#include <vector>

enum class SquareType
{
    Wall,
    Space,
    StartPos,
    SpawnPoint
};

class GameMap
{
public:
    GameMap(const std::string &filename);

    const uint16_t sizeX() const;

    const uint16_t sizeY() const;

    const SquareType getSquareType(const uint16_t posX, const uint16_t posY) const;

    uint16_t getStartPosX() const;

    uint16_t getStartPosY() const;

    uint16_t getSpawnPointX() const;

    uint16_t getSpawnPointY() const;

private:
    void loadFromFile(const std::string &filename);

    void checkIntegrity();

    std::vector<std::vector<SquareType>> squares;

    const SquareType symbolToSquareType(const char symbol) const;

    uint16_t startPosX;
    uint16_t startPosY;

    uint16_t spawnPointX;
    uint16_t spawnPointY;

};


#endif //PACMAN_GAMEMAP_H
