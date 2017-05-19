#ifndef PACMAN_COORDINATES_H
#define PACMAN_COORDINATES_H


#include <cstdint>
#include "Direction.h"

/**
 * @brief Represents a single square position (integral) on the game map
 */
class Coordinates
{
public:
    Coordinates(const int32_t x, const int32_t y);

    Coordinates();

    /**
     * @brief Gets a position relative to this one
     * @param direction
     * @param distance
     * @return
     * @throws std::logic_error on unhandled direction
     */
    const Coordinates relative(const Direction direction) const;

    friend bool operator==(const Coordinates &lhs, const Coordinates &rhs);

    friend bool operator!=(const Coordinates &lhs, const Coordinates &rhs);

    friend bool operator<(const Coordinates &lhs, const Coordinates &rhs);

    friend bool operator>(const Coordinates &lhs, const Coordinates &rhs);

    friend bool operator<=(const Coordinates &lhs, const Coordinates &rhs);

    friend bool operator>=(const Coordinates &lhs, const Coordinates &rhs);

    int32_t x; /**< @brief Axis X value */
    int32_t y; /**< @brief Axis Y value */
};


#endif //PACMAN_COORDINATES_H
