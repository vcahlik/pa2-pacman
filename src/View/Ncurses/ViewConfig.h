#ifndef PACMAN_NCURSESCONFIG_H
#define PACMAN_NCURSESCONFIG_H


#include <cstdint>

namespace ViewConfig
{
    const uint32_t SQUARE_SIZE_X = 6;
    const uint32_t SQUARE_SIZE_Y = 3;

    const uint32_t STATUS_BAR_SIZE_X = 1;

    const Color GAME_BACKGROUND_COLOR = Color::Black;

    const Color BORDER_COLOR = Color::Cyan;
    const Color STATUS_BAR_TEXT_COLOR = Color::Cyan;

    const Color COLOR_PLAYER = Color::Yellow;
    const Color COLOR_WALL = Color::Blue;
    const Color COLOR_COIN = Color::Yellow;
    const Color COLOR_SPAWNPOINT = Color::Blue;

    const char * const STATUS_BAR_TEXT_REMAINING_LIVES = "Extra lives: ";
    const char * const STATUS_BAR_TEXT_GAME_OVER = "GAME OVER";
    const char * const STATUS_BAR_TEXT_GAME_WON = "YOU WIN!";
    const char * const STATUS_BAR_TEXT_SCORE = "Score: ";
}


#endif //PACMAN_NCURSESCONFIG_H
