#ifndef PACMAN_ENEMY_H
#define PACMAN_ENEMY_H


#include "../MovableObject.h"

class Enemy
    : public MovableObject
{
public:
    explicit Enemy(const Position position, const double speed, const double size, Game *game);

    virtual const bool performActions() override;

protected:
    void chooseRandomDirection();

};


#endif //PACMAN_ENEMY_H
