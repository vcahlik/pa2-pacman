#ifndef PACMAN_GHOST_H
#define PACMAN_GHOST_H


#include "Enemy.h"

class Ghost
    : public Enemy
{
public:
    explicit Ghost(const double posX, const double posY, const double speed, Game *game);

protected:
    virtual void navigate() override;

};


#endif //PACMAN_GHOST_H
