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
        init_pair(colorCode(Color::White), toNcursesColor(Color::White), toNcursesColor(ViewConfig::GAME_BACKGROUND_COLOR));
        init_pair(colorCode(Color::Black), toNcursesColor(Color::Black), toNcursesColor(ViewConfig::GAME_BACKGROUND_COLOR));
        init_pair(colorCode(Color::Yellow), toNcursesColor(Color::Yellow), toNcursesColor(ViewConfig::GAME_BACKGROUND_COLOR));
        init_pair(colorCode(Color::Blue), toNcursesColor(Color::Blue), toNcursesColor(ViewConfig::GAME_BACKGROUND_COLOR));
        init_pair(colorCode(Color::Green), toNcursesColor(Color::Green), toNcursesColor(ViewConfig::GAME_BACKGROUND_COLOR));
        init_pair(colorCode(Color::Red), toNcursesColor(Color::Red), toNcursesColor(ViewConfig::GAME_BACKGROUND_COLOR));
        init_pair(colorCode(Color::Cyan), toNcursesColor(Color::Cyan), toNcursesColor(ViewConfig::GAME_BACKGROUND_COLOR));
        init_pair(colorCode(Color::Magenta), toNcursesColor(Color::Magenta), toNcursesColor(ViewConfig::GAME_BACKGROUND_COLOR));
    }

    const int16_t colorCode(const Color color)
    {
        return static_cast<int16_t>(color);
    }

    const int16_t toNcursesColor(const Color color)
    {
        switch (color)
        {
            case Color::White:
                return COLOR_WHITE;
            case Color::Black:
                return COLOR_BLACK;
            case Color::Yellow:
                return COLOR_YELLOW;
            case Color::Blue:
                return COLOR_BLUE;
            case Color::Green:
                return COLOR_GREEN;
            case Color::Red:
                return COLOR_RED;
            case Color::Cyan:
                return COLOR_CYAN;
            case Color::Magenta:
                return COLOR_MAGENTA;
            default:
                throw std::invalid_argument("Color not translated yet");
        }
    }
}