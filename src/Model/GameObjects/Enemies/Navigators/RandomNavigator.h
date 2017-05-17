#ifndef PACMAN_RANDOMNAVIGATOR_H
#define PACMAN_RANDOMNAVIGATOR_H


#include "Navigator.h"
#include "../../../../Position.h"
#include "../../GameObject.h"

class RandomNavigator
    : public Navigator
{
public:
    explicit RandomNavigator(const MovableObject &client, const GameMap &map);

    virtual const Direction navigate(const MovableObject &object) const override;

};


#endif //PACMAN_RANDOMNAVIGATOR_H
