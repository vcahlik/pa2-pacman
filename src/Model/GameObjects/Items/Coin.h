#ifndef PACMAN_COIN_H
#define PACMAN_COIN_H


#include "ScoreBonus.h"

class Coin
    : public ScoreBonus
{
public:
    Coin(const double posX, const double posY, Game *game);

};


#endif //PACMAN_COIN_H
