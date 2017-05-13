#ifndef PACMAN_GAMEMAP_H
#define PACMAN_GAMEMAP_H

#include <string>
#include <vector>

enum class SquareType
{
    Wall,
    Space,
    SpawnPoint,
    Teleport
};

class MovableObject;

class GameMap
{
public:
    explicit GameMap(const std::string &filename);

    const uint32_t sizeX() const;

    const uint32_t sizeY() const;

    const SquareType getSquareType(const uint32_t posX, const uint32_t posY) const;

    const bool isIntersectionForObject(const uint32_t posX, const uint32_t posY, const MovableObject &object) const;

    const uint32_t getStartPosX() const;

    const uint32_t getStartPosY() const;

    const uint32_t getSpawnPointPosX() const;

    const uint32_t getSpawnPointPosY() const;

    const uint32_t getOtherTeleportEndPosX(const uint32_t entryPosX, const uint32_t entryPosY) const;

    const uint32_t getOtherTeleportEndPosY(const uint32_t entryPosX, const uint32_t entryPosY) const;

private:
    class SquarePosition
    {
    public:
        SquarePosition(const uint32_t x, const uint32_t y);
        SquarePosition();

        uint32_t x;
        uint32_t y;
    };

    enum class MapFileSymbol
    {
        Wall,
        Space,
        SpawnPoint,
        StartPos,
        Teleport
    };

    void loadFromFile(const std::string &filename);

    void checkIntegrity();

    std::vector<std::vector<SquareType>> squares;

    const MapFileSymbol charToMapFileSymbol(const char character) const;

    const SquareType mapFileSymbolToSquareType(const MapFileSymbol mapFileSymbol) const;

    uint32_t teleportSquaresCount;

    SquarePosition startPos;
    SquarePosition spawnPointPos;
    SquarePosition teleportAPos;
    SquarePosition teleportBPos;
};


#endif //PACMAN_GAMEMAP_H
