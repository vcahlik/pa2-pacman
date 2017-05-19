#include "ScoreBonus.h"
#include "../../Game.h"

ScoreBonus::ScoreBonus(const Position position, const double size, const uint32_t scoreReward, Game *game)
    : Item(position, size, game),
      scoreReward(scoreReward)
{

}

void ScoreBonus::performActions()
{
    Item::performActions();

    if (state == State::Removed)
    {
        game->increaseScore(scoreReward);
    }
}
