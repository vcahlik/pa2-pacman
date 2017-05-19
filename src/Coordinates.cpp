#include <stdexcept>
#include "Coordinates.h"
#include "Direction.h"

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

bool operator<(const Coordinates &lhs, const Coordinates &rhs)
{
    if (lhs.x < rhs.x)
        return true;
    if (rhs.x < lhs.x)
        return false;
    return lhs.y < rhs.y;
}

bool operator>(const Coordinates &lhs, const Coordinates &rhs)
{
    return rhs < lhs;
}

bool operator<=(const Coordinates &lhs, const Coordinates &rhs)
{
    return !(rhs < lhs);
}

bool operator>=(const Coordinates &lhs, const Coordinates &rhs)
{
    return !(lhs < rhs);
}
