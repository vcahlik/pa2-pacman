#ifndef PACMAN_CONFIG_H
#define PACMAN_CONFIG_H


#include <cstdint>

namespace Config
{
    const uint16_t GRID_SIZE = 10;

    const char MAP_FILE_SYMBOL_WALL = 'H';
    const char MAP_FILE_SYMBOL_SPACE = ' ';
    const char MAP_FILE_SYMBOL_STARTPOS = 'P';
    const char MAP_FILE_SYMBOL_SPAWNPOINT = 'S';

}


#endif //PACMAN_CONFIG_H
