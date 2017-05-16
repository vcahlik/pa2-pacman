#ifndef PACMAN_RANDOMNAVIGATOR_H
#define PACMAN_RANDOMNAVIGATOR_H


#include "Navigator.h"
#include "../../../../Position.h"
#include "../../GameObject.h"

class RandomNavigator
    : public Navigator
{
public:
    RandomNavigator(const MovableObject &client);

    virtual const Direction navigate(const MovableObject &object, const bool navigateCloser) const override;

};


#endif //PACMAN_RANDOMNAVIGATOR_H
