#ifndef PACMAN_GAMEOBJECT_H
#define PACMAN_GAMEOBJECT_H


#include <cstdint>
#include "../../Position.h"
#include "../GameMap.h"

class Game;

class GameObject
{
public:
    explicit GameObject(const Position position, const double size, Game *game);

    virtual const bool performActions() = 0;

    virtual const bool isCompatibleSquareType(const SquareType squareType) const;

    const bool isCollision(const GameObject &other) const;

    const Position &getPosition() const;

protected:
    const Position getCenteredPosition(const Position rawPosition) const;

    Game *game;

    Position position;

private:
    const double size;

};


#endif //PACMAN_GAMEOBJECT_H
