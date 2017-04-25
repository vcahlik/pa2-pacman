#include "GameWindow.h"
#include "NcursesUtils.h"
#include "ViewConfig.h"

GameWindow::GameWindow(const std::string &mapFile, NcursesView &view)
    : game(mapFile),
      window(nullptr),
      view(view)
{
    sizeX = 2 + game.getMap().sizeX() * ViewConfig::SQUARE_SIZE_X;
    sizeY = 2 + game.getMap().sizeY() * ViewConfig::SQUARE_SIZE_Y;
    posX = (COLS - sizeX) / 2;
    posY = (LINES - sizeY) / 2;
}

void GameWindow::takeControl()
{
    window = NcursesUtils::createWindow(sizeY, sizeX, posY, posX);


    drawGame();
    getch();


    NcursesUtils::destroyWindow(window);
    window = nullptr;
}

void GameWindow::drawGame()
{
    for (uint32_t y = 0; y < game.getMap().sizeY(); ++y)
    {
        for (uint32_t x = 0; x < game.getMap().sizeX(); ++x)
        {
            SquareType type = game.getMap().getSquareType(x, y);
            if (type == SquareType::Wall)
            {
                mvwprintw(window, y * ViewConfig::SQUARE_SIZE_Y + 1, x * ViewConfig::SQUARE_SIZE_X + 1, "888888");
                mvwprintw(window, y * ViewConfig::SQUARE_SIZE_Y + 2, x * ViewConfig::SQUARE_SIZE_X + 1, "888888");
                mvwprintw(window, y * ViewConfig::SQUARE_SIZE_Y + 3, x * ViewConfig::SQUARE_SIZE_X + 1, "888888");
            }
        }
    }

    wrefresh(window);
}
