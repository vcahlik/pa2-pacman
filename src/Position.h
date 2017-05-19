#ifndef PACMAN_POSITION_H
#define PACMAN_POSITION_H

#include "Direction.h"
#include "Coordinates.h"

/**
 * @brief Represents an exact decimal position in a hypothetic real-number 2D space
 */
class Position
{
public:
    Position(const double x, const double y);

    Position();

    /**
     * @brief Copy constructor from Coordinates
     * @param coord
     */
    Position(const Coordinates coord);

    /**
     * @brief Returns equivalent Coordinates, discarding the decimal part
     * @return
     */
    const Coordinates toCoord() const;

    /**
     * @brief Determines whether the position is integral, e.g. possible valid Coordinates
     * @return
     */
    const bool isOnCoordinateGrid() const;

    /**
     * @brief Gets a position relative to this one
     * @param direction
     * @param distance
     * @return
     * @throws std::logic_error on unhandled direction
     */
    const Position relative(const Direction direction, const double distance) const;

    friend bool operator==(const Position &lhs, const Position &rhs);

    friend bool operator!=(const Position &lhs, const Position &rhs);

    friend bool operator<(const Position &lhs, const Position &rhs);

    friend bool operator>(const Position &lhs, const Position &rhs);

    friend bool operator<=(const Position &lhs, const Position &rhs);

    friend bool operator>=(const Position &lhs, const Position &rhs);

    double x; /**< @brief Axis X value */
    double y; /**< @brief Axis Y value */
};


#endif //PACMAN_POSITION_H
