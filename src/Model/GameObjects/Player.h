#ifndef PACMAN_PLAYER_H
#define PACMAN_PLAYER_H


#include "MovableObject.h"

class MovableObject;
class Player
    : public MovableObject
{
public:
    Player(const double posX, const double posY, Game *game);

    virtual void performActions() override;

    void requestGoUp();

    void requestGoDown();

    void requestGoLeft();

    void requestGoRight();

    const bool isMouthOpen() const;

protected:
    virtual void navigate() override;

    void navigateAtIntersection();

    void animateMouth();

    Direction requestedDirection;

    bool mouthOpen;
    uint32_t mouthOpenMsecs;

};


#endif //PACMAN_PLAYER_H
