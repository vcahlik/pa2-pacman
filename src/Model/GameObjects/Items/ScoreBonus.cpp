#include "ScoreBonus.h"
#include "../../Game.h"

ScoreBonus::ScoreBonus(const double posX, const double posY, const double size, const uint32_t scoreReward, Game *game)
    : Item(posX, posY, size, game),
      scoreReward(scoreReward)
{

}

const bool ScoreBonus::performActions()
{
    bool retVal = Item::performActions();
    bool pickedUp = !retVal;

    if (pickedUp)
    {
        game->addScore(scoreReward);
    }

    return retVal;
}
