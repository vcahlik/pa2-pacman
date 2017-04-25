#ifndef PACMAN_NCURSESUTILS_H
#define PACMAN_NCURSESUTILS_H


#include <ncurses.h>

namespace NcursesUtils
{
    WINDOW *createWindow(uint16_t height, uint16_t width, uint16_t posY, uint16_t posX);

    void destroyWindow(WINDOW *window);
}


#endif //PACMAN_NCURSESUTILS_H
