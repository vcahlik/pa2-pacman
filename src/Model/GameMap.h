#ifndef PACMAN_GAMEMAP_H
#define PACMAN_GAMEMAP_H

#include <string>
#include <vector>
#include <set>
#include "../Position.h"

/**
 * @brief Types of different game map squares
 */
enum class SquareType
{
    Wall,
    Space,
    SpawnPoint,
    Teleport
};

class GameObject;
class MovableObject;

/**
 * @brief Represents the game board and locations of different squares
 */
class GameMap
{
public:
    /**
     * @brief Constructor which directly loads the map from specified file
     * @param filename
     * @throws ExceptionMessage on map file processing error
     */
    explicit GameMap(const std::string &filename);

    const uint32_t getSizeX() const;

    const uint32_t getSizeY() const;

    /**
     * @brief Gets the type of square at given Coordinates
     * @param coord
     * @return
     * @throws std::out_of_range on coordinates ot within map size
     */
    const SquareType getSquareType(const Coordinates coord) const;

    /**
     * @brief Determine whether the coordinate represents a logical intersection for given object
     * @param coord
     * @param object
     * @return
     *
     * Intersection means that the square is not a corridor of compatible squares within non-compatible squares
     */
    const bool isIntersectionForObject(const Coordinates coord, const MovableObject &object) const;

    /**
     * @brief Returns Coordinates of a random square compatible with given object
     * @param object
     * @return
     */
    const Coordinates getRandomCompatibleCoord(const GameObject &object) const;

    /**
     * @brief Checks if the Coordinates are within map
     * @param coord
     * @return
     */
    const bool isCoordinatesWithinMap(const Coordinates coord) const;

    const Coordinates getStartPosCoordinates() const;

    const Coordinates getSpawnPointCoordinates() const;

    /**
     * @brief Returns coordinates of the other teleport end (represented by its Coordinates)
     * @param entryPosCoord
     * @return
     * @throws Utils::ExceptionMessage if entered Coordinates is not a teleport
     */
    const Coordinates getOtherTeleportEndCoordinates(const Coordinates entryPosCoord) const;

    const std::set<Coordinates> getPowerUpLocations() const;

private:
    /**
     * @brief All types of symbols which can be stored in a map file
     */
    enum class MapFileSymbol
    {
        Wall,
        Space,
        SpawnPoint,
        StartPos,
        Teleport,
        PowerUp
    };

    /**
     * @brief Attempts to read a valid map from given map file
     * @param filename
     * @throws Utils::ExceptionMessage on i/o error or a non-valid map
     */
    void loadFromFile(const std::string &filename);

    /**
     * @brief Simple map sanity check, helper for loadFromFile()
     * @throws Utils::ExceptionMessage on integrity error
     */
    void checkIntegrity() const;

    /**
     * @brief Helper for checkIntegrity()
     * @throws Utils::ExceptionMessage if not all border squares are walls or teleports
     */
    void checkMapHasBorderWalls() const;

    std::vector<std::vector<SquareType>> squares; /**< @brief Memory representation of map */

    /**
     * @brief Converts a map file character to a MapFileSymbol
     * @param character
     * @return
     * @throws ExceptionMessage on invalid symbol
     */
    const MapFileSymbol charToMapFileSymbol(const char character) const;

    /**
     * @brief Converts a MapFileSymbol to a corresponding SquareType
     * @param mapFileSymbol
     * @return
     * @throws std::logic_error on unhandled MapFileSymbol
     */
    const SquareType mapFileSymbolToSquareType(const MapFileSymbol mapFileSymbol) const;

    uint32_t teleportSquaresCount;
    bool startPosSet;
    bool spawnPointSet;

    Coordinates startPosCoord;
    Coordinates spawnPointCoord;
    Coordinates teleportACoord;
    Coordinates teleportBCoord;

    std::set<Coordinates> powerUpLocations;

};


#endif //PACMAN_GAMEMAP_H
