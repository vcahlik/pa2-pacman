#ifndef PACMAN_NCURSESUTILS_H
#define PACMAN_NCURSESUTILS_H


#include <ncurses.h>
#include "Color.h"

namespace NcursesUtils
{
    WINDOW *createWindow(uint16_t height, uint16_t width, uint16_t posY, uint16_t posX);

    void destroyWindow(WINDOW *window);

    void initColors();

    const int16_t colorCode(const Color color);
}


#endif //PACMAN_NCURSESUTILS_H
