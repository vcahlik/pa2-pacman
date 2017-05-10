#ifndef PACMAN_UTILS_H
#define PACMAN_UTILS_H


#include "Direction.h"

namespace Utils
{
    const double decimalPart(const double value);

    const bool areOppositeDirections(const Direction direction, const Direction newDirection);

    const uint32_t getRandom(const uint32_t interval);
}


#endif //PACMAN_UTILS_H
