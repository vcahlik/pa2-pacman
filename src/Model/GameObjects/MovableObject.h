#ifndef PACMAN_MOVABLEOBJECT_H
#define PACMAN_MOVABLEOBJECT_H


#include "GameObject.h"
#include "../../Direction.h"
#include "../GameMap.h"

class GameObject;

class MovableObject
        : public GameObject
{
public:
    explicit MovableObject(const Position position, const double speed, const double size, Game *game);

    virtual void performActions() override;

    const Direction getDirection() const;

    const Direction getRandomValidDirection() const;

    const Direction getRandomDifferentValidDirection(const Direction usedDirection) const;

    const bool isValidDirection(const Direction direction) const;

    const bool isOnlyValidDirection(const Direction newDirection) const;

protected:
    virtual void chooseDirection() = 0;

    virtual void move();

    const double stepSize(const double speed) const;

    const bool isHorizontalDirection(const Direction direction) const;

    const bool isVerticalDirection(const Direction direction) const;

    const bool noValidDirectionExists() const;

    double baseSpeed;
    double speed;
    Direction direction;

};


#endif //PACMAN_MOVABLEOBJECT_H
