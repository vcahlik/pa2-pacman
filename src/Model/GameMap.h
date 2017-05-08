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
    explicit GameMap(const std::string &filename);

    const uint32_t sizeX() const;

    const uint32_t sizeY() const;

    const SquareType getSquareType(const uint32_t posX, const uint32_t posY) const;

    const bool isIntersection(const uint32_t posX, const uint32_t posY) const;

    const bool squareCanBeEntered(const uint32_t posX, const uint32_t posY) const;

    const uint32_t getStartPosX() const;

    const uint32_t getStartPosY() const;

    const uint32_t getSpawnPointX() const;

    const uint32_t getSpawnPointY() const;

private:
    void loadFromFile(const std::string &filename);

    void checkIntegrity();

    std::vector<std::vector<SquareType>> squares;

    const SquareType symbolToSquareType(const char symbol) const;

    uint32_t startPosX;
    uint32_t startPosY;

    uint32_t spawnPointX;
    uint32_t spawnPointY;

};


#endif //PACMAN_GAMEMAP_H
