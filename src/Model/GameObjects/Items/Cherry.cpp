#include "Cherry.h"
#include "../../../Config.h"

Cherry::Cherry(const double posX, const double posY, Game *game)
        : ScoreBonus(posX, posY, Config::CHERRY_SIZE, Config::CHERRY_SCORE_BONUS, game)
{
    timer.requestTimer(Timeout::CherryLifetime);
}

const bool Cherry::performActions()
{
    timer.notifyOfNextCycle();

    if (!ScoreBonus::performActions() || timer.isTimeoutEvent(Timeout::CherryLifetime))
    {
        return false;
    }

    return true;
}
