#include "Coin.h"
#include "../../../Config.h"
#include "../../Game.h"

Coin::Coin(const double posX, const double posY, Game *game)
    : Item(posX, posY, Config::COIN_SIZE, game)
{}
