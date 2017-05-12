#include "Coin.h"
#include "../../../Config.h"
#include "../../Game.h"

Coin::Coin(const double posX, const double posY, Game *game)
    : ScoreBonus(posX, posY, Config::COIN_SIZE, Config::COIN_SCORE_BONUS, game)
{}
