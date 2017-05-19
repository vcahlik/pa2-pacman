#ifndef PACMAN_RANDOMNAVIGATOR_H
#define PACMAN_RANDOMNAVIGATOR_H


#include "Navigator.h"
#include "../../../../Position.h"
#include "../../GameObject.h"

/**
 * @brief Pseudorandom navigator, arbitrary changes in direction in 180 degrees are not allowed
 */
class RandomNavigator
    : public Navigator
{
public:
    explicit RandomNavigator(const MovableObject &owner, const GameMap &map);

    virtual const Direction navigate(const MovableObject &target) const override;

};


#endif //PACMAN_RANDOMNAVIGATOR_H
