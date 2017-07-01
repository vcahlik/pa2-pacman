#ifndef PACMAN_GAMEOBJECT_H
#define PACMAN_GAMEOBJECT_H


#include <cstdint>
#include "Position.h"
#include "Model/GameMap.h"

class Game;

/**
 * @brief Any abstract entity which can be present on the game board and be drawn by View
 */
class GameObject
{
public:
    explicit GameObject(const Position position, const double size, Game *game);

    virtual void performActions() = 0;

    /**
     * @brief Checks if GameObject could possibly be placed on a given SquareType
     * @param squareType
     * @return
     */
    virtual const bool isCompatibleSquareType(const SquareType squareType) const;

    /**
     * @brief Checks if collides with the other GameObject
     * @param other
     * @return
     */
    const bool isCollision(const GameObject &other) const;

    const Position &getPosition() const;

protected:
    /**
     * @brief Returns position which would place the GameObject into the square center, based on its size
     * @param rawPosition
     * @return
     */
    const Position getCenteredPosition(const Position rawPosition) const;

    Game *game;

    Position position;

private:
    const double size;

};


#endif //PACMAN_GAMEOBJECT_H
