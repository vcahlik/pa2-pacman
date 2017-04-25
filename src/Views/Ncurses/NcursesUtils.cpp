#include "NcursesUtils.h"

namespace NcursesUtils
{
    WINDOW *createWindow(uint16_t height, uint16_t width, uint16_t posY, uint16_t posX)
    {
        WINDOW *window;

        window = newwin(height, width, posY, posX);
        box(window, 0 , 0);
        wrefresh(window);

        return window;
    }

    void destroyWindow(WINDOW *window)
    {
        wborder(window, ' ', ' ', ' ',' ',' ',' ',' ',' ');
        wrefresh(window);
        delwin(window);
    }
}
