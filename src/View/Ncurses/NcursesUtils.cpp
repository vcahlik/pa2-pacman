#include "NcursesUtils.h"
#include "Color.h"
#include "ViewConfig.h"

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

    void initColors()
    {
        init_pair(colorCode(Color::YELLOW), COLOR_YELLOW, ViewConfig::GAME_BACKGROUND_COLOR);
        init_pair(colorCode(Color::MAGENTA), COLOR_MAGENTA, ViewConfig::GAME_BACKGROUND_COLOR);
    }

    const int16_t colorCode(const Color color)
    {
        return static_cast<int16_t>(color);
    }
}
