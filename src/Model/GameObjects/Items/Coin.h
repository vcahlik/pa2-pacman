#ifndef PACMAN_COIN_H
#define PACMAN_COIN_H


#include "ScoreBonus.h"

class Coin
    : public ScoreBonus
{
public:
    explicit Coin(const Position position, Game *game);

};


#endif //PACMAN_COIN_H
