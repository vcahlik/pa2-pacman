#ifndef PACMAN_NCURSESCONFIG_H
#define PACMAN_NCURSESCONFIG_H


#include <cstdint>

namespace ViewConfig
{
    const uint32_t SQUARE_SIZE_X = 6;
    const uint32_t SQUARE_SIZE_Y = 3;

    const Color GAME_BACKGROUND_COLOR = Color::Black;

    const Color COLOR_PLAYER = Color::Yellow;
    const Color COLOR_WALL = Color::Magenta;
    const Color COLOR_COIN = Color::Yellow;
    const Color COLOR_SPAWNPOINT = Color::Magenta;
}


#endif //PACMAN_NCURSESCONFIG_H
