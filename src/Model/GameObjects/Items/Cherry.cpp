#include "Cherry.h"
#include "../../../Config.h"
#include "../../../Utils.h"
#include "../../Game.h"

Cherry::Cherry(Game *game)
        : ScoreBonus(0, 0, Config::CHERRY_SIZE, Config::CHERRY_SCORE_BONUS, game)
{
    placeOnRandomPosition();

    timer.requestTimer(Timeout::CherryLifetime);
}

const bool Cherry::performActions()
{
    timer.notifyOfNextCycle();

    if (!ScoreBonus::performActions())
    {
        return false;
    }

    return !timer.isTimeoutEvent(Timeout::CherryLifetime);
}

void Cherry::placeOnRandomPosition()
{
    uint32_t candidatePosX = 0;
    uint32_t candidatePosY = 0;

    while (true)
    {
        candidatePosX = Utils::getRandom(game->getMap().sizeX());
        candidatePosY = Utils::getRandom(game->getMap().sizeY());
        if (isCompatiblePosition(candidatePosX, candidatePosY))
        {
            posX = calculateCenteredPos(candidatePosX, getSize());
            posY = calculateCenteredPos(candidatePosY, getSize());
            break;
        }
    }
}

const bool Cherry::isCompatiblePosition(const uint32_t posX, const uint32_t posY) const
{
    const SquareType squareType = game->getMap().getSquareType(posX, posY);
    return (squareType == SquareType::Space ||
            squareType == SquareType::StartPos);
}
