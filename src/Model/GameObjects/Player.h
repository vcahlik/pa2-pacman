#ifndef PACMAN_PLAYER_H
#define PACMAN_PLAYER_H


#include "MovableObject.h"

class MovableObject;
class Player
    : public MovableObject
{
public:
    explicit Player(const double posX, const double posY, Game *game);

    virtual const bool performActions() override;

    void requestGoUp();

    void requestGoDown();

    void requestGoLeft();

    void requestGoRight();

    virtual const bool isEnterableSquareType(const SquareType squareType) const override;

    const bool isAlive() const;

    void die();

    const bool isMouthOpen() const;

protected:
    virtual void navigate() override;

    void navigateAtIntersection();

    void animateMouth();

    Direction requestedDirection;

    bool alive;
    bool mouthOpen;
    uint32_t mouthOpenMsecs;

};


#endif //PACMAN_PLAYER_H
