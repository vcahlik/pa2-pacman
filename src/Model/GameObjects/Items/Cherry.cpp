#include "Cherry.h"
#include "../../../Config.h"
#include "../../../Utils.h"
#include "../../Game.h"

Cherry::Cherry(Game *game)
        : ScoreBonus(Position(), Config::CHERRY_SIZE, Config::CHERRY_SCORE_BONUS, game)
{
    // Place on random position
    position = getCenteredPosition(game->getMap().getRandomCompatibleCoord(*this));

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
