#include <stdexcept>
#include "NcursesUtils.h"
#include "Color.h"
#include "ViewConfig.h"

namespace NcursesUtils
{
    void initNcurses()
    {
        initscr();

        timeout(0);
        cbreak();
        noecho();
        curs_set(false);
        refresh();

        if (!has_colors())
        {
            endwin();
            throw std::runtime_error("Terminal does not support colors");
        }

        start_color();
        NcursesUtils::initColors();
    }

    void endNcurses()
    {
        endwin();
    }

    WINDOW *createWindow(uint32_t height, uint32_t width, uint32_t posY, uint32_t posX)
    {
        WINDOW *window;

        window = newwin(height, width, posY, posX);
        wtimeout(window, 0);
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

    const int32_t colorCode(const Color color)
    {
        return static_cast<int32_t>(color);
    }
}
