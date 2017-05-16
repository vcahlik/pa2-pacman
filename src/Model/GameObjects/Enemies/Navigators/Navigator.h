#ifndef PACMAN_NAVIGATOR_H
#define PACMAN_NAVIGATOR_H


#include "../../../../Direction.h"
#include "../../GameObject.h"

enum class NavigatorType
{
    Random
};

class Navigator
{
public:
    Navigator(const MovableObject &client);

    virtual const Direction navigate(const MovableObject &object, const bool navigateCloser) const = 0;

protected:
    const MovableObject &client;

};


#endif //PACMAN_NAVIGATOR_H
