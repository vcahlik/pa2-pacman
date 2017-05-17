#ifndef PACMAN_NAVIGATOR_H
#define PACMAN_NAVIGATOR_H


#include "../../../../Direction.h"
#include "../../GameObject.h"

enum class NavigatorType
{
    Random,
    BfsNavigator
};

class Navigator
{
public:
    Navigator(const MovableObject &client, const GameMap &map);

    virtual const Direction navigate(const MovableObject &object) const = 0;

protected:
    const MovableObject &client;
    const GameMap &map;

};


#endif //PACMAN_NAVIGATOR_H
