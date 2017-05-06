#ifndef PACMAN_COIN_H
#define PACMAN_COIN_H


#include "Item.h"

class Coin
    : public Item
{
public:
    Coin(const double posX, const double posY, Game *game);

};


#endif //PACMAN_COIN_H
