#include "Coin.h"
#include "Config.h"
#include "Model/Game.h"

Coin::Coin(const Position position, Game *game)
        : ScoreBonus(position, Config::COIN_SIZE, Config::COIN_SCORE_BONUS, game) {

}
