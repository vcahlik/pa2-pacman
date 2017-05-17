#ifndef PACMAN_POWERUP_H
#define PACMAN_POWERUP_H


#include "Item.h"

class PowerUp
    : public Item
{
public:
    PowerUp(const Position &position, Game *game);

    void performActions() override;

};


#endif //PACMAN_POWERUP_H
