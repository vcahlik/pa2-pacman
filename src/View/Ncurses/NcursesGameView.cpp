#include <termcap.h>
#include <stdexcept>
#include <iostream>
#include "NcursesGameView.h"
#include "NcursesUtils.h"
#include "ViewConfig.h"
#include "TextGraphics.h"

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
    wclear(window);

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
                uint32_t posX = x * ViewConfig::SQUARE_SIZE_X + 1;
                uint32_t posY = y * ViewConfig::SQUARE_SIZE_Y + 1;
                mvwprintw(window, posY, posX, TextGraphics::Wall::NORMAL_LINE1);
                mvwprintw(window, posY + 1, posX, TextGraphics::Wall::NORMAL_LINE2);
                mvwprintw(window, posY + 2, posX, TextGraphics::Wall::NORMAL_LINE3);
            }
        }
    }
    wattroff(window, COLOR_PAIR(NcursesUtils::colorCode(Color::MAGENTA)));
}

void NcursesGameView::drawObjects() const
{
    drawPlayer();
}

void NcursesGameView::drawPlayer() const
{
    double x = game->getPlayer().getPosX();
    double y = game->getPlayer().getPosY();

    const char *line1 = nullptr;
    const char *line2 = nullptr;
    const char *line3 = nullptr;

    if (!game->getPlayer().isMouthOpen())
    {
        line1 = TextGraphics::Player::MOUTH_CLOSED_LINE1;
        line2 = TextGraphics::Player::MOUTH_CLOSED_LINE2;
        line3 = TextGraphics::Player::MOUTH_CLOSED_LINE3;
    } else
    {
        switch (game->getPlayer().getDirection())
        {
            case Direction::UP:
                line1 = TextGraphics::Player::MOUTH_OPEN_UP_LINE1;
                line2 = TextGraphics::Player::MOUTH_OPEN_UP_LINE2;
                line3 = TextGraphics::Player::MOUTH_OPEN_UP_LINE3;
                break;
            case Direction::DOWN:
                line1 = TextGraphics::Player::MOUTH_OPEN_DOWN_LINE1;
                line2 = TextGraphics::Player::MOUTH_OPEN_DOWN_LINE2;
                line3 = TextGraphics::Player::MOUTH_OPEN_DOWN_LINE3;
                break;
            case Direction::LEFT:
                line1 = TextGraphics::Player::MOUTH_OPEN_LEFT_LINE1;
                line2 = TextGraphics::Player::MOUTH_OPEN_LEFT_LINE2;
                line3 = TextGraphics::Player::MOUTH_OPEN_LEFT_LINE3;
                break;
            case Direction::RIGHT:
            default:
                line1 = TextGraphics::Player::MOUTH_OPEN_RIGHT_LINE1;
                line2 = TextGraphics::Player::MOUTH_OPEN_RIGHT_LINE2;
                line3 = TextGraphics::Player::MOUTH_OPEN_RIGHT_LINE3;
                break;
        }
    }

    wattron(window, COLOR_PAIR(NcursesUtils::colorCode(Color::YELLOW)));
    mvwprintw(window, y * ViewConfig::SQUARE_SIZE_Y + 1, x * ViewConfig::SQUARE_SIZE_X + 1, line1);
    mvwprintw(window, y * ViewConfig::SQUARE_SIZE_Y + 2, x * ViewConfig::SQUARE_SIZE_X + 1, line2);
    mvwprintw(window, y * ViewConfig::SQUARE_SIZE_Y + 3, x * ViewConfig::SQUARE_SIZE_X + 1, line3);
    wattroff(window, COLOR_PAIR(NcursesUtils::colorCode(Color::YELLOW)));
}

const InputKey NcursesGameView::getPressedKey() const
{
    int32_t c = wgetch(window);

    if (c == 27 && wgetch(window) == 91) // Special encoding of arrow keys
    {
        c = wgetch(window);
        switch (c)
        {
            case 'A':
                return InputKey::UP;
            case 'B':
                return InputKey::DOWN;
            case 'D':
                return InputKey::LEFT;
            case 'C':
                return InputKey::RIGHT;
            default:
                throw NoUserInputException();
        }
    } else
    {
        throw NoUserInputException();
    }
}
