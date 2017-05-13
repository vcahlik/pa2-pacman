#include <termcap.h>
#include <stdexcept>
#include <sstream>
#include "NcursesGameView.h"
#include "NcursesUtils.h"
#include "ViewConfig.h"
#include "TextGraphics.h"

NcursesGameView::NcursesGameView(const Game *game)
    : game(game), window(nullptr)
{
    sizeX = 2 + game->getMap().sizeX() * ViewConfig::SQUARE_SIZE_X;
    sizeY = 2 + game->getMap().sizeY() * ViewConfig::SQUARE_SIZE_Y + ViewConfig::STATUS_BAR_SIZE_X;
    posX = (COLS - sizeX) / 2;
    posY = (LINES - sizeY) / 2;
}

void NcursesGameView::show()
{
    window = NcursesUtils::createWindow(sizeY, sizeX, posY, posX);
    wbkgd(window, COLOR_PAIR(NcursesUtils::colorCode(ViewConfig::GAME_BACKGROUND_COLOR)));
    notimeout(window, true);
}

void NcursesGameView::redraw()
{
    wclear(window);

    drawBorder();

    drawStatusBar();

    drawMap();

    drawGameObjects();

    wrefresh(window);
}

void NcursesGameView::end()
{
    NcursesUtils::destroyWindow(window);
    window = nullptr;
}

void NcursesGameView::drawBorder() const
{
    wattron(window, COLOR_PAIR(NcursesUtils::colorCode(ViewConfig::BORDER_COLOR)));
    wborder(window, '|', '|', '-', '-', '+', '+', '+', '+');
    wattroff(window, COLOR_PAIR(NcursesUtils::colorCode(ViewConfig::BORDER_COLOR)));
}

void NcursesGameView::drawStatusBar() const
{
    std::stringstream textRemainingLives;
    std::stringstream textScore;
    std::stringstream textMessage;

    textRemainingLives << ViewConfig::STATUS_BAR_TEXT_REMAINING_LIVES << game->getRemainingLivesCount();
    textScore << ViewConfig::STATUS_BAR_TEXT_SCORE << game->getScore();

    if (game->getState() == GameState::GameWon)
    {
        textMessage << ViewConfig::STATUS_BAR_TEXT_GAME_WON;
    } else if (game->getState() == GameState::GameOver)
    {
        textMessage << ViewConfig::STATUS_BAR_TEXT_GAME_OVER;
    }

    wattron(window, COLOR_PAIR(NcursesUtils::colorCode(ViewConfig::STATUS_BAR_TEXT_COLOR)));
    mvwprintw(window, 1, 1, textRemainingLives.str().c_str());
    mvwprintw(window, 1, static_cast<int>((sizeX - textMessage.str().length()) / 2), textMessage.str().c_str());
    mvwprintw(window, 1, static_cast<int>(sizeX - textScore.str().length() - 1), textScore.str().c_str());
    wattroff(window, COLOR_PAIR(NcursesUtils::colorCode(ViewConfig::STATUS_BAR_TEXT_COLOR)));
}

void NcursesGameView::drawMap() const
{
    drawWalls();
    drawSpawnPoint();
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
                drawTextGraphics(TextGraphics::Wall::LINE1, 1, x, y, ViewConfig::COLOR_WALL);
                drawTextGraphics(TextGraphics::Wall::LINE2, 2, x, y, ViewConfig::COLOR_WALL);
                drawTextGraphics(TextGraphics::Wall::LINE3, 3, x, y, ViewConfig::COLOR_WALL);
            }
        }
    }
}

void NcursesGameView::drawSpawnPoint() const
{
    double x = game->getMap().getSpawnPointPosX();
    double y = game->getMap().getSpawnPointPosY();

    const char *line1 = TextGraphics::SpawnPoint::LINE1;
    const char *line2 = TextGraphics::SpawnPoint::LINE2;
    const char *line3 = TextGraphics::SpawnPoint::LINE3;

    drawTextGraphics(line1, 1, x, y, ViewConfig::COLOR_SPAWNPOINT);
    drawTextGraphics(line2, 2, x, y, ViewConfig::COLOR_SPAWNPOINT);
    drawTextGraphics(line3, 3, x, y, ViewConfig::COLOR_SPAWNPOINT);
}

void NcursesGameView::drawGameObjects() const
{
    drawObject(game->getPlayer());

    for (const auto &coin : game->getCoins())
    {
        drawObject(*coin);
    }

    for (const auto &ghost : game->getGhosts())
    {
        drawObject(*ghost);
    }

    if (game->isCherryPresent())
    {
        drawObject(game->getCherry());
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

void NcursesGameView::drawObject(const Cherry &cherry) const
{
    double x = cherry.getPosX();
    double y = cherry.getPosY();

    drawTextGraphics(TextGraphics::CHERRY_LINE1, 0, x, y, ViewConfig::COLOR_CHERRY_TWIG);
    drawTextGraphics(TextGraphics::CHERRY_LINE2, 1, x, y, ViewConfig::COLOR_CHERRY_FRUIT);
}

void NcursesGameView::drawObject(const Ghost &ghost) const
{
    double x = ghost.getPosX();
    double y = ghost.getPosY();

    const char *line1 = nullptr;
    const char *line2 = nullptr;
    const char *line3 = nullptr;

    switch (ghost.getDirection())
    {
        case Direction::LEFT:
            line1 = TextGraphics::Ghost::LEFT_LINE1;
            line2 = TextGraphics::Ghost::LEFT_LINE2;
            line3 = TextGraphics::Ghost::LEFT_LINE3;
            break;
        case Direction::RIGHT:
        default:
            line1 = TextGraphics::Ghost::RIGHT_LINE1;
            line2 = TextGraphics::Ghost::RIGHT_LINE2;
            line3 = TextGraphics::Ghost::RIGHT_LINE3;
            break;
    }

    drawTextGraphics(line1, 1, x, y, ghost.getColor());
    drawTextGraphics(line2, 2, x, y, ghost.getColor());
    drawTextGraphics(line3, 3, x, y, ghost.getColor());
}

void NcursesGameView::drawTextGraphics(const char *const text, const uint32_t lineNo, const double x, const double y, const Color color) const
{
    wattron(window, COLOR_PAIR(NcursesUtils::colorCode(color)));
    mvwprintw(window,
              static_cast<uint32_t>(y * ViewConfig::SQUARE_SIZE_Y + lineNo + ViewConfig::STATUS_BAR_SIZE_X),
              static_cast<uint32_t>(x * ViewConfig::SQUARE_SIZE_X + 1),
              text);
    wattroff(window, COLOR_PAIR(NcursesUtils::colorCode(color)));
}

const InputKey NcursesGameView::getPressedKey() const
{
    // TODO document: may throw!
    return NcursesUtils::getPressedKey(window);
}
