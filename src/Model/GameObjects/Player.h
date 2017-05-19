#ifndef PACMAN_PLAYER_H
#define PACMAN_PLAYER_H


#include "MovableObject.h"

class MovableObject;

/**
 * @brief The player's character
 */
class Player
    : public MovableObject
{
public:
    explicit Player(const Position position, Game *game);

    virtual void performActions() override;

    /**
     * @brief Player will go up once it is possible
     */
    void requestGoUp();

    /**
     * @brief Player will go down once it is possible
     */
    void requestGoDown();

    /**
     * @brief Player will go left once it is possible
     */
    void requestGoLeft();

    /**
     * @brief Player will go right once it is possible
     */
    void requestGoRight();

    /**
     * @brief Teleports player to the other teleport end
     */
    void teleport();

    virtual const bool isCompatibleSquareType(const SquareType squareType) const override;

    const bool isAlive() const;

    void die();

    const bool isMouthOpen() const;

protected:
    /**
     * @brief Overrides the player's request for next direction
     * @param newDirection
     */
    void setMasterDirection(const Direction newDirection);

    virtual void chooseDirection() override;

    /**
     * @brief Called on positions where Player could possible change his direction
     */
    void navigateAtGridPosition();

    void animateMouth();

    Direction requestedDirection;

    bool alive;
    bool mouthOpen;
    uint32_t mouthOpenMsecs;

};


#endif //PACMAN_PLAYER_H
