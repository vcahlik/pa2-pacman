#ifndef PACMAN_MOVABLEOBJECT_H
#define PACMAN_MOVABLEOBJECT_H


#include "GameObject.h"

class GameObject;
class MovableObject
    : public GameObject
{
public:
    MovableObject(const double posX, const double posY, const double speed, Game *game);

    double baseSpeed;
    double speedX;
    double speedY;

};


#endif //PACMAN_MOVABLEOBJECT_H
