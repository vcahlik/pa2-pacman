#include <termcap.h>
#include <stdexcept>
#include <sstream>
#include "NcursesGameView.h"
#include "NcursesUtils.h"
#include "ViewConfig.h"
#include "TextGraphics.h"
#include "Utils.h"

NcursesGameView::NcursesGameView(const Game *game)
        : game(game), window(nullptr) {
    sizeX = 2 + game->getMap().getSizeX() * ViewConfig::SQUARE_SIZE_X;
    sizeY = 2 + game->getMap().getSizeY() * ViewConfig::SQUARE_SIZE_Y + ViewConfig::STATUS_BAR_SIZE_X;

    if (static_cast<uint32_t>(COLS) < sizeX || static_cast<uint32_t>(LINES) < sizeY) {
        throw Utils::ExceptionMessage("Your terminal window is too small");
    }

    // Center the canvas
    posX = (COLS - sizeX) / 2;
    posY = (LINES - sizeY) / 2;
}

void NcursesGameView::show() {
    window = NcursesUtils::createWindow(sizeY, sizeX, posY, posX);
    wbkgd(window, COLOR_PAIR(NcursesUtils::colorCode(ViewConfig::GAME_BACKGROUND_COLOR)));
    notimeout(window, true);
}

void NcursesGameView::redraw() {
    wclear(window);

    drawBorder();

    drawStatusBar();

    drawMap();

    drawGameObjects();

    wrefresh(window);
}

void NcursesGameView::end() {
    NcursesUtils::destroyWindow(window);
    window = nullptr;
}

void NcursesGameView::drawBorder() const {
    wattron(window, COLOR_PAIR(NcursesUtils::colorCode(ViewConfig::BORDER_COLOR)));
    wborder(window, '|', '|', '-', '-', '+', '+', '+', '+');
    wattroff(window, COLOR_PAIR(NcursesUtils::colorCode(ViewConfig::BORDER_COLOR)));
}

void NcursesGameView::drawStatusBar() const {
    std::stringstream textRemainingLives;
    std::stringstream textScore;
    std::stringstream textMessage;

    textRemainingLives << ViewConfig::STATUS_BAR_TEXT_REMAINING_LIVES << game->getRemainingLivesCount();
    textScore << ViewConfig::STATUS_BAR_TEXT_SCORE << game->getScore();

    if (game->getState() == Game::State::GameWon) {
        textMessage << ViewConfig::STATUS_BAR_TEXT_GAME_WON;
    } else if (game->getState() == Game::State::GameOver) {
        textMessage << ViewConfig::STATUS_BAR_TEXT_GAME_OVER;
    }

    wattron(window, COLOR_PAIR(NcursesUtils::colorCode(ViewConfig::STATUS_BAR_TEXT_COLOR)));
    mvwprintw(window, 1, 1, textRemainingLives.str().c_str());
    mvwprintw(window, 1, static_cast<int>((sizeX - textMessage.str().length()) / 2), textMessage.str().c_str());
    mvwprintw(window, 1, static_cast<int>(sizeX - textScore.str().length() - 1), textScore.str().c_str());
    wattroff(window, COLOR_PAIR(NcursesUtils::colorCode(ViewConfig::STATUS_BAR_TEXT_COLOR)));
}

void NcursesGameView::drawMap() const {
    for (uint32_t y = 0; y < game->getMap().getSizeY(); ++y) {
        for (uint32_t x = 0; x < game->getMap().getSizeX(); ++x) {
            Coordinates coord(x, y);
            switch (game->getMap().getSquareType(coord)) {
                case SquareType::Wall:
                    drawWall(coord);
                    break;
                case SquareType::Teleport:
                    drawTeleport(coord);
                    break;
                case SquareType::SpawnPoint:
                    drawSpawnPoint(coord);
                    break;
                default:
                    break;
            }
        }
    }
}

void NcursesGameView::drawWall(const Coordinates coord) const {
    drawTextGraphics(TextGraphics::Wall::LINE1, 1, coord, ViewConfig::COLOR_WALL);
    drawTextGraphics(TextGraphics::Wall::LINE2, 2, coord, ViewConfig::COLOR_WALL);
    drawTextGraphics(TextGraphics::Wall::LINE3, 3, coord, ViewConfig::COLOR_WALL);
}

void NcursesGameView::drawTeleport(const Coordinates coord) const {
    const char *line1 = TextGraphics::Teleport::LINE1;
    const char *line2 = TextGraphics::Teleport::LINE2;
    const char *line3 = TextGraphics::Teleport::LINE3;

    drawTextGraphics(line1, 1, coord, ViewConfig::COLOR_SPAWNPOINT);
    drawTextGraphics(line2, 2, coord, ViewConfig::COLOR_SPAWNPOINT);
    drawTextGraphics(line3, 3, coord, ViewConfig::COLOR_SPAWNPOINT);
}

void NcursesGameView::drawSpawnPoint(const Coordinates coord) const {
    const char *line1 = TextGraphics::SpawnPoint::LINE1;
    const char *line2 = TextGraphics::SpawnPoint::LINE2;
    const char *line3 = TextGraphics::SpawnPoint::LINE3;

    drawTextGraphics(line1, 1, coord, ViewConfig::COLOR_SPAWNPOINT);
    drawTextGraphics(line2, 2, coord, ViewConfig::COLOR_SPAWNPOINT);
    drawTextGraphics(line3, 3, coord, ViewConfig::COLOR_SPAWNPOINT);
}

void NcursesGameView::drawGameObjects() const {
    drawObject(game->getPlayer());

    for (const auto &coin : game->getCoins()) {
        drawObject(*coin);
    }

    for (const auto &ghost : game->getGhosts()) {
        drawObject(*ghost);
    }

    for (const auto &powerUp : game->getPowerUps()) {
        drawObject(*powerUp);
    }

    if (game->isCherryPresent()) {
        drawObject(game->getCherry());
    }
}

void NcursesGameView::drawObject(const Player &player) const {
    const char *line1 = nullptr;
    const char *line2 = nullptr;
    const char *line3 = nullptr;

    if (!player.isMouthOpen()) {
        line1 = TextGraphics::Player::MOUTH_CLOSED_LINE1;
        line2 = TextGraphics::Player::MOUTH_CLOSED_LINE2;
        line3 = TextGraphics::Player::MOUTH_CLOSED_LINE3;
    } else {
        switch (player.getDirection()) {
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

    drawTextGraphics(line1, 1, player.getPosition(), ViewConfig::COLOR_PLAYER);
    drawTextGraphics(line2, 2, player.getPosition(), ViewConfig::COLOR_PLAYER);
    drawTextGraphics(line3, 3, player.getPosition(), ViewConfig::COLOR_PLAYER);
}

void NcursesGameView::drawObject(const Coin &coin) const {
    drawTextGraphics(TextGraphics::COIN, 1, coin.getPosition(), ViewConfig::COLOR_COIN);
}

void NcursesGameView::drawObject(const Cherry &cherry) const {
    drawTextGraphics(TextGraphics::CHERRY_LINE1, 0, cherry.getPosition(), ViewConfig::COLOR_CHERRY_TWIG);
    drawTextGraphics(TextGraphics::CHERRY_LINE2, 1, cherry.getPosition(), ViewConfig::COLOR_CHERRY_FRUIT);
}

void NcursesGameView::drawObject(const Ghost &ghost) const {
    if (ghost.getState() == Ghost::State::InGhostHouse) {
        return;
    }

    const char *line1 = nullptr;
    const char *line2 = nullptr;
    const char *line3 = nullptr;

    switch (ghost.getDirection()) {
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

    drawTextGraphics(line1, 1, ghost.getPosition(), ghost.getColor());
    drawTextGraphics(line2, 2, ghost.getPosition(), ghost.getColor());
    drawTextGraphics(line3, 3, ghost.getPosition(), ghost.getColor());
}

void NcursesGameView::drawObject(const PowerUp &powerUp) const {
    drawTextGraphics(TextGraphics::POWERUP, 1, powerUp.getPosition(), ViewConfig::COLOR_POWERUP);
}

void NcursesGameView::drawTextGraphics(const char *const text, const uint32_t lineNo, const Position position,
                                       const Color color) const {
    wattron(window, COLOR_PAIR(NcursesUtils::colorCode(color)));
    mvwprintw(window,
              static_cast<uint32_t>(position.y * ViewConfig::SQUARE_SIZE_Y + lineNo + ViewConfig::STATUS_BAR_SIZE_X),
              static_cast<uint32_t>(position.x * ViewConfig::SQUARE_SIZE_X + 1),
              text);
    wattroff(window, COLOR_PAIR(NcursesUtils::colorCode(color)));
}

const InputKey NcursesGameView::getPressedKey() const {
    // TODO document: may throw!
    return NcursesUtils::getPressedKey(window);
}
