#ifndef PACMAN_UTILS_H
#define PACMAN_UTILS_H


#include "Direction.h"
#include <stdexcept>

namespace Utils
{
    class ExceptionMessage
        : public std::runtime_error
    {
    public:
        ExceptionMessage(const std::string &message);
    };

    const double decimalPart(const double value);

    const bool areOppositeDirections(const Direction direction, const Direction newDirection);

    const uint32_t getRandom(const uint32_t interval);
}


#endif //PACMAN_UTILS_H
