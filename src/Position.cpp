#include <cstdint>
#include <stdexcept>
#include "Position.h"
#include "Utils.h"

Position::Position(const double x, const double y)
    : x(x), y(y)
{
}

Position::Position()
{
}

Position::Position(const Coordinates coord)
    : x(coord.x), y(coord.y)
{
}

const Coordinates Position::toCoord() const
{
    return Coordinates(static_cast<uint32_t>(x), static_cast<uint32_t>(y));
}

const bool Position::isOnCoordinateGrid() const
{
    return Utils::decimalPart(x) == 0 &&
           Utils::decimalPart(y) == 0;
}

const Position Position::relative(const Direction direction, const double distance) const
{
    switch (direction)
    {
        case Direction::UP:
            return Position(x, y - distance);
        case Direction::DOWN:
            return Position(x, y + distance);
        case Direction::LEFT:
            return Position(x - distance, y);
        case Direction::RIGHT:
            return Position(x + distance, y);
        case Direction::NONE:
            return Position(x, y);
        default:
            throw std::logic_error("Unhandled direction");
    }
}

bool operator==(const Position &lhs, const Position &rhs)
{
    return lhs.x == rhs.x &&
           lhs.y == rhs.y;
}

bool operator!=(const Position &lhs, const Position &rhs)
{
    return !(rhs == lhs);
}

Coordinates::Coordinates(const int32_t x, const int32_t y)
        : x(x), y(y)
{
}

Coordinates::Coordinates()
{
}

const Coordinates Coordinates::relative(const Direction direction) const
{
    switch (direction)
    {
        case Direction::UP:
            return Coordinates(x, y - 1);
        case Direction::DOWN:
            return Coordinates(x, y + 1);
        case Direction::LEFT:
            return Coordinates(x - 1, y);
        case Direction::RIGHT:
            return Coordinates(x + 1, y);
        case Direction::NONE:
            return Coordinates(x, y);
        default:
            throw std::logic_error("Unhandled direction");
    }
}

bool operator==(const Coordinates &lhs, const Coordinates &rhs)
{
    return lhs.x == rhs.x &&
           lhs.y == rhs.y;
}

bool operator!=(const Coordinates &lhs, const Coordinates &rhs)
{
    return !(rhs == lhs);
}
