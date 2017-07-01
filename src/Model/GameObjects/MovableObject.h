#ifndef PACMAN_MOVABLEOBJECT_H
#define PACMAN_MOVABLEOBJECT_H


#include "GameObject.h"
#include "Direction.h"
#include "Model/GameMap.h"

class GameObject;

/**
 * @brief Abstract GameObject which can move
 */
class MovableObject
        : public GameObject
{
public:
    explicit MovableObject(const Position position, const double speed, const double size, Game *game);

    virtual void performActions() override;

    const Direction getDirection() const;

    /**
     * @brief Checks if direction leads to a compatible square type
     * @return
     */
    const bool isValidDirection(const Direction direction) const;

    /**
     * @brief Returns any non-zero valid direction, or Direction::NONE if none exists
     * @return
     */
    const Direction getRandomValidDirection() const;

    const Direction getRandomDifferentValidDirection(const Direction usedDirection) const;

    /**
     * @brief Checks if given direction is the only valid non-zero direction
     * @param newDirection
     * @return
     * @throws std::logic_error if the given direction is not valid
     */
    const bool isOnlyValidDirection(const Direction newDirection) const;

protected:
    /**
     * @brief Determines where to move
     */
    virtual void chooseDirection() = 0;

    /**
     * @brief Changes position according to speed and direction
     */
    virtual void move();

    /**
     * @brief Calculates resulting move distance
     * @param speed
     * @return
     */
    const double stepSize(const double speed) const;

    const bool isHorizontalDirection(const Direction direction) const;

    const bool isVerticalDirection(const Direction direction) const;

    const bool noValidDirectionExists() const;

    double baseSpeed;
    double speed;
    Direction direction;

};


#endif //PACMAN_MOVABLEOBJECT_H
