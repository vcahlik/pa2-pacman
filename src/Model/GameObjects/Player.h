#ifndef PACMAN_PLAYER_H
#define PACMAN_PLAYER_H


#include "MovableObject.h"

class MovableObject;
class Player
    : public MovableObject
{
public:
    Player(const double posX, const double posY, Game *game);

    virtual void performActions();

};


#endif //PACMAN_PLAYER_H
