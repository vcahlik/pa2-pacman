#include "NcursesGameView.h"
#include "NcursesUtils.h"
#include "ViewConfig.h"

NcursesGameView::NcursesGameView(const Game *game)
    : game(game), window(nullptr)
{
    sizeX = 2 + game->getMap().sizeX() * ViewConfig::SQUARE_SIZE_X;
    sizeY = 2 + game->getMap().sizeY() * ViewConfig::SQUARE_SIZE_Y;
    posX = (COLS - sizeX) / 2;
    posY = (LINES - sizeY) / 2;
}

void NcursesGameView::show()
{
    window = NcursesUtils::createWindow(sizeY, sizeX, posY, posX);
}

void NcursesGameView::redraw()
{
    drawWalls();

    drawObjects();

    wrefresh(window);
}

void NcursesGameView::end()
{
    NcursesUtils::destroyWindow(window);
    window = nullptr;
}

void NcursesGameView::drawWalls() const
{
    wattron(window, COLOR_PAIR(NcursesUtils::colorCode(Color::MAGENTA)));
    for (uint32_t y = 0; y < game->getMap().sizeY(); ++y)
    {
        for (uint32_t x = 0; x < game->getMap().sizeX(); ++x)
        {
            SquareType type = game->getMap().getSquareType(x, y);
            if (type == SquareType::Wall)
            {
                mvwprintw(window, y * ViewConfig::SQUARE_SIZE_Y + 1, x * ViewConfig::SQUARE_SIZE_X + 1, "888888");
                mvwprintw(window, y * ViewConfig::SQUARE_SIZE_Y + 2, x * ViewConfig::SQUARE_SIZE_X + 1, "888888");
                mvwprintw(window, y * ViewConfig::SQUARE_SIZE_Y + 3, x * ViewConfig::SQUARE_SIZE_X + 1, "888888");
            }
        }
    }
    wattroff(window, COLOR_PAIR(NcursesUtils::colorCode(Color::MAGENTA)));
}

void NcursesGameView::drawObjects() const
{
    double x = game->getPlayer().getPosX();
    double y = game->getPlayer().getPosY();

    wattron(window, COLOR_PAIR(NcursesUtils::colorCode(Color::YELLOW)));
    mvwprintw(window, y * ViewConfig::SQUARE_SIZE_Y + 1, x * ViewConfig::SQUARE_SIZE_X + 1, " CCCC ");
    mvwprintw(window, y * ViewConfig::SQUARE_SIZE_Y + 2, x * ViewConfig::SQUARE_SIZE_X + 1, "CCCCCC");
    mvwprintw(window, y * ViewConfig::SQUARE_SIZE_Y + 3, x * ViewConfig::SQUARE_SIZE_X + 1, " CCCC ");
    wattroff(window, COLOR_PAIR(NcursesUtils::colorCode(Color::YELLOW)));
}
