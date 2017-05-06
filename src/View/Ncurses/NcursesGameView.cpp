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
    wbkgd(window, COLOR_PAIR(NcursesUtils::colorCode(ViewConfig::GAME_BACKGROUND_COLOR)));
}

void NcursesGameView::redraw()
{
    wclear(window);

    drawWalls();

    drawGameObjects();

    wrefresh(window);
}

void NcursesGameView::end()
{
    NcursesUtils::destroyWindow(window);
    window = nullptr;
}

void NcursesGameView::drawWalls() const
{
    for (uint32_t y = 0; y < game->getMap().sizeY(); ++y)
    {
        for (uint32_t x = 0; x < game->getMap().sizeX(); ++x)
        {
            SquareType type = game->getMap().getSquareType(x, y);
            if (type == SquareType::Wall)
            {
                drawTextGraphics(TextGraphics::Wall::NORMAL_LINE1, 1, x, y, ViewConfig::COLOR_WALL);
                drawTextGraphics(TextGraphics::Wall::NORMAL_LINE1, 2, x, y, ViewConfig::COLOR_WALL);
                drawTextGraphics(TextGraphics::Wall::NORMAL_LINE1, 3, x, y, ViewConfig::COLOR_WALL);
            }
        }
    }
}

void NcursesGameView::drawGameObjects() const
{
    drawObject(game->getPlayer());

    for (const auto &coin : game->getCoins())
    {
        drawObject(*coin);
    }
}

void NcursesGameView::drawObject(const Player &player) const
{
    double x = player.getPosX();
    double y = player.getPosY();

    const char *line1 = nullptr;
    const char *line2 = nullptr;
    const char *line3 = nullptr;

    if (!player.isMouthOpen())
    {
        line1 = TextGraphics::Player::MOUTH_CLOSED_LINE1;
        line2 = TextGraphics::Player::MOUTH_CLOSED_LINE2;
        line3 = TextGraphics::Player::MOUTH_CLOSED_LINE3;
    } else
    {
        switch (player.getDirection())
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

    drawTextGraphics(line1, 1, x, y, ViewConfig::COLOR_PLAYER);
    drawTextGraphics(line2, 2, x, y, ViewConfig::COLOR_PLAYER);
    drawTextGraphics(line3, 3, x, y, ViewConfig::COLOR_PLAYER);
}

void NcursesGameView::drawObject(const Coin &coin) const
{
    double x = coin.getPosX();
    double y = coin.getPosY();

    drawTextGraphics(TextGraphics::COIN, 1, x, y, ViewConfig::COLOR_COIN);
}

void NcursesGameView::drawTextGraphics(const char *const text, const uint32_t lineNo, const double x, const double y, const Color color) const
{
    wattron(window, COLOR_PAIR(NcursesUtils::colorCode(color)));
    mvwprintw(window, y * ViewConfig::SQUARE_SIZE_Y + lineNo, x * ViewConfig::SQUARE_SIZE_X + 1, text);
    wattroff(window, COLOR_PAIR(NcursesUtils::colorCode(color)));
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
