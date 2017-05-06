#ifndef PACMAN_MOVABLEOBJECT_H
#define PACMAN_MOVABLEOBJECT_H


#include "GameObject.h"
#include "../../Direction.h"

class GameObject;

class MovableObject
        : public GameObject
{
public:
    explicit MovableObject(const double posX, const double posY, const double speed, const double size, Game *game);

    virtual const bool performActions() override;

    const Direction getDirection() const;

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
