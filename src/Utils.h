#ifndef PACMAN_UTILS_H
#define PACMAN_UTILS_H


#include "Direction.h"
#include <stdexcept>

namespace Utils
{
    /**
     * @brief Exception used for printing console errors (outside of Ncurses)
     */
    class ExceptionMessage
        : public std::runtime_error
    {
    public:
        ExceptionMessage(const std::string &message);
    };

    /**
     * @brief Gets the decimal value of a double
     * @param value
     * @return
     */
    const double decimalPart(const double value);

    /**
     * @brief Returns true if two directions are directly opposite, such as UP/DOWN
     * @param direction
     * @param newDirection
     * @return
     * @throws std::logic_error on unhandled direction
     */
    const bool areOppositeDirections(const Direction direction, const Direction newDirection);

    /**
     * @brief Random integer generator
     * @param interval Maximal return value, exclusive
     * @return
     */
    const uint32_t getRandom(const uint32_t interval);
}


#endif //PACMAN_UTILS_H
