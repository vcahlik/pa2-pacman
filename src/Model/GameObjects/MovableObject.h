#ifndef PACMAN_MOVABLEOBJECT_H
#define PACMAN_MOVABLEOBJECT_H


#include "GameObject.h"
#include "../../Direction.h"

class GameObject;

class MovableObject
        : public GameObject
{
public:
    MovableObject(const double posX, const double posY, const double speed, Game *game);

    virtual void performActions() override;

protected:
    virtual void move();

    virtual void navigate() = 0;

    const bool validDirection(const Direction direction) const;

    const double stepSize(const double speed) const;

    const bool isOnGrid() const;

    const double nextGridPosition(const double position, const double step) const;

    const bool isHorizontalDirection(const Direction direction) const;

    const bool isVerticalDirection(const Direction direction) const;

    double baseSpeed;
    double speed;
    Direction direction;

};


#endif //PACMAN_MOVABLEOBJECT_H
