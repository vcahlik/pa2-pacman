#ifndef PACMAN_POSITION_H
#define PACMAN_POSITION_H

#include "Direction.h"

class Coordinates;

class Position
{
public:
    Position(const double x, const double y);

    Position();

    Position(const Coordinates coord);

    const Coordinates toCoord() const;

    const bool isOnCoordinateGrid() const;

    const Position relative(const Direction direction, const double distance) const;

    friend bool operator==(const Position &lhs, const Position &rhs);

    friend bool operator!=(const Position &lhs, const Position &rhs);

    double x;
    double y;
};

class Coordinates
{
public:
    Coordinates(const int32_t x, const int32_t y);

    Coordinates();

    const Coordinates relative(const Direction direction) const;

    friend bool operator==(const Coordinates &lhs, const Coordinates &rhs);

    friend bool operator!=(const Coordinates &lhs, const Coordinates &rhs);

    int32_t x;
    int32_t y;
};


#endif //PACMAN_POSITION_H
