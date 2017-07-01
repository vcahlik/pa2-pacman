#ifndef PACMAN_COIN_H
#define PACMAN_COIN_H


#include "ScoreBonus.h"

/**
 * @brief Bonus, Player wins once all coins have been collected
 */
class Coin
        : public ScoreBonus
{
public:
    explicit Coin(const Position position, Game *game);

};


#endif //PACMAN_COIN_H
