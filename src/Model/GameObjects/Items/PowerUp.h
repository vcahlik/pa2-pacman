#ifndef PACMAN_POWERUP_H
#define PACMAN_POWERUP_H


#include "Item.h"

/**
 * @brief Item whose collection frightens other ghosts
 */
class PowerUp
    : public Item
{
public:
    PowerUp(const Position &position, Game *game);

    void performActions() override;

};


#endif //PACMAN_POWERUP_H
