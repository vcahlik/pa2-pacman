#ifndef PACMAN_CONFIG_H
#define PACMAN_CONFIG_H


#include <cstdint>

namespace Config
{
    const char MAP_FILE_SYMBOL_WALL = 'H';
    const char MAP_FILE_SYMBOL_SPACE = ' ';
    const char MAP_FILE_SYMBOL_STARTPOS = 'P';
    const char MAP_FILE_SYMBOL_SPAWNPOINT = 'S';

    const double PLAYER_BASE_SPEED = 0.5;

    const uint16_t REFRESH_TIME_USECS = 50;
}


#endif //PACMAN_CONFIG_H
