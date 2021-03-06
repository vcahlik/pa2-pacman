#ifndef PACMAN_CONFIG_H
#define PACMAN_CONFIG_H


#include <cstdint>
#include "Difficulty.h"
#include "View/Ncurses/Color.h"

/**
 * @brief Configuration of the game logic
 */
namespace Config
{
    const char MAP_FILE_SYMBOL_WALL = 'H';
    const char MAP_FILE_SYMBOL_SPACE = ' ';
    const char MAP_FILE_SYMBOL_STARTPOS = '<';
    const char MAP_FILE_SYMBOL_SPAWNPOINT = 'o';
    const char MAP_FILE_SYMBOL_TELEPORT = '\\';
    const char MAP_FILE_SYMBOL_POWERUP = '.';

    const double PLAYER_BASE_SPEED = 2.5;
    const double PLAYER_SIZE = 1;
    const uint32_t PLAYER_MOUTH_PERIOD_MSECS = 220;

    const double COIN_SIZE = 0.33;
    const uint32_t COIN_SCORE_BONUS = 10;

    const double CHERRY_SIZE = 0.33;
    const uint32_t CHERRY_SCORE_BONUS = 100;
    const uint32_t CHERRY_LIFETIME_MSECS = 7000;
    const uint32_t CHERRY_GENERATION_INTERVAL_MSECS = 20000;

    const double POWERUP_SIZE = 0.33;

    const double GHOST_SIZE = 1;
    const double GHOST_FRIGHTENED_SPEED_RATIO = 0.7;

    const uint32_t GHOST_FRIGHTENED_DEFAULT_DURATION_MSECS = 6000;
    const uint32_t GHOST_FRIGHTENED_END_DURATION_MSECS = 2000;
    const uint32_t GHOST_FRIGHTENED_BLINK_INTERVAL_MSECS = 200;

    const uint32_t GHOST_FREAK_FAST_MODE_ENABLE_RANDOM_PERIOD = 12;
    const uint32_t GHOST_FREAK_FAST_MODE_DISABLE_RANDOM_PERIOD = 3;

    const Color GHOST_FRIGHTENED_COLOR = Color::Blue;
    const Color GHOST_NORMAL_COLOR = Color::Magenta;
    const Color GHOST_AGGRESSIVE_COLOR = Color::Red;
    const Color GHOST_FREAK_COLOR = Color::Green;

    const Difficulty::Level DEFAULT_DIFFICULTY_LEVEL = Difficulty::Level::Level3;

    const uint32_t GHOST_GENERATION_TIME_MSECS = 3000;

    const uint32_t CYCLE_TIME_MSECS = 50;

    const uint32_t PLAYER_VICTORY_SCREEN_TIME_MSECS = 2000;
    const uint32_t PLAYER_DEATH_SCREEN_TIME_MSECS = 2000;
    const uint32_t PLAYER_GAME_OVER_SCREEN_TIME_MSECS = 2000;
}


#endif //PACMAN_CONFIG_H
