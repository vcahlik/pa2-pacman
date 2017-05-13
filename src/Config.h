#ifndef PACMAN_CONFIG_H
#define PACMAN_CONFIG_H


#include <cstdint>
#include "Difficulty.h"

namespace Config
{
    const char MAP_FILE_SYMBOL_WALL = 'H';
    const char MAP_FILE_SYMBOL_SPACE = ' ';
    const char MAP_FILE_SYMBOL_STARTPOS = 'P';
    const char MAP_FILE_SYMBOL_SPAWNPOINT = 'S';

    const double PLAYER_BASE_SPEED = 2.5;
    const double PLAYER_SIZE = 1;
    const uint32_t PLAYER_MOUTH_PERIOD_MSECS = 220;

    const double COIN_SIZE = 0.33;
    const uint32_t COIN_SCORE_BONUS = 10;

    const double CHERRY_SIZE = 0.33;
    const uint32_t CHERRY_SCORE_BONUS = 100;
    const uint32_t CHERRY_LIFETIME_MSECS = 1000;
    const uint32_t CHERRY_GENERATION_INTERVAL_MSECS = 1000;

    const double GHOST_SIZE = 1;
    const double GHOST_BASE_SPEED = 1.8;

    const Difficulty DEFAULT_DIFFICULTY = Difficulty::DIF1;
    const uint32_t INITIAL_REMAINING_LIVES = 2;
    const uint32_t GHOST_COUNT = 1;

    const uint32_t GHOST_GENERATION_TIME_MSECS = 2000;

    const uint32_t CYCLE_TIME_MSECS = 50;

    const uint32_t PLAYER_VICTORY_SCREEN_TIME_MSECS = 2000;
    const uint32_t PLAYER_DEATH_SCREEN_TIME_MSECS = 2000;
    const uint32_t PLAYER_GAME_OVER_SCREEN_TIME_MSECS = 2000;
}


#endif //PACMAN_CONFIG_H
