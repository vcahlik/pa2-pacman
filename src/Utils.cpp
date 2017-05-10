#include <cmath>
#include <stdexcept>
#include "Utils.h"

namespace Utils
{
    const double decimalPart(const double value)
    {
        double temp;
        return std::modf(value, &temp);
    }

    const bool areOppositeDirections(const Direction direction, const Direction newDirection)
    {
        switch (direction)
        {
            case Direction::UP:
                return (newDirection == Direction::DOWN);
            case Direction::DOWN:
                return (newDirection == Direction::UP);
            case Direction::LEFT:
                return (newDirection == Direction::RIGHT);
            case Direction::RIGHT:
                return (newDirection == Direction::LEFT);
            case Direction::NONE:
                return false;
            default:
                throw std::logic_error("direction not handled");
        }
    }

    const uint32_t getRandom(const uint32_t interval)
    {
        return abs(rand()) % interval;
    }
}
