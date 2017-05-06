#ifndef PACMAN_NCURSESUTILS_H
#define PACMAN_NCURSESUTILS_H


#include <ncurses.h>
#include "Color.h"
#include "../../InputKey.h"

namespace NcursesUtils
{
    WINDOW *initNcurses();

    void endNcurses();

    WINDOW *createWindow(uint32_t height, uint32_t width, uint32_t posY, uint32_t posX);

    void destroyWindow(WINDOW *window);

    void initColors();

    const int16_t colorCode(const Color color);

    const int16_t toNcursesColor(const Color color);

    const InputKey getPressedKey(WINDOW *window);

}


#endif //PACMAN_NCURSESUTILS_H
