#ifndef PACMAN_GAMEMAP_H
#define PACMAN_GAMEMAP_H

#include <string>
#include <vector>
#include "../Position.h"

enum class SquareType
{
    Wall,
    Space,
    SpawnPoint,
    Teleport
};

class GameObject;
class MovableObject;

class GameMap
{
public:
    explicit GameMap(const std::string &filename);

    const uint32_t sizeX() const;

    const uint32_t sizeY() const;

    const SquareType getSquareType(const Coordinates coord) const;

    const bool isIntersectionForObject(const Coordinates coord, const MovableObject &object) const;

    const Coordinates getRandomCompatibleCoord(const GameObject &object) const;

    const bool coordinatesWithinMap(const Coordinates coord) const;

    const Coordinates getStartPosCoordinates() const;

    const Coordinates getSpawnPointCoordinates() const;

    const Coordinates getOtherTeleportEndCoordinates(const Coordinates entryPosCoord) const;

private:
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

    Coordinates startPosCoord;
    Coordinates spawnPointCoord;
    Coordinates teleportACoord;
    Coordinates teleportBCoord;

};


#endif //PACMAN_GAMEMAP_H
