#include "Cherry.h"
#include "../../../Config.h"

Cherry::Cherry(const double posX, const double posY, Game *game)
        : ScoreBonus(posX, posY, Config::CHERRY_SIZE, Config::CHERRY_SCORE_BONUS, game)
{}
