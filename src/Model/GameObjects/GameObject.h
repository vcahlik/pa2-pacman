#ifndef PACMAN_GAMEOBJECT_H
#define PACMAN_GAMEOBJECT_H


#include <cstdint>

class Game;

class GameObject
{
public:
    GameObject(const double posX, const double posY, Game *game);

    virtual void performActions() = 0;

    const double getPosX() const;

    const double getPosY() const;

protected:
    Game *game;

    double posX;
    double posY;

private:

};


#endif //PACMAN_GAMEOBJECT_H
