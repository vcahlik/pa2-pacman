#include "MovableObject.h"

MovableObject::MovableObject(const double posX, const double posY, const double speed, Game *game)
        : GameObject(posX, posY, game),
          baseSpeed(speed),
          speedX(0), speedY(0)
{

}
