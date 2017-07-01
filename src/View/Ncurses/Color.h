#ifndef PACMAN_COLOR_H
#define PACMAN_COLOR_H


#include <cstdint>

/**
 * @brief Representation of colors, better than the Ncurses one
 */
enum class Color
        : int32_t
{
    White = 1,
    Black,
    Yellow,
    Blue,
    Green,
    Red,
    Cyan,
    Magenta
};


#endif //PACMAN_COLOR_H
