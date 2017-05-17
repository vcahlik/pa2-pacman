#ifndef PACMAN_ESCAPENAVIGATOR_H
#define PACMAN_ESCAPENAVIGATOR_H


#include "Navigator.h"

class EscapeNavigator
    : public Navigator
{
public:
    EscapeNavigator(const MovableObject &client, const GameMap &map);

    const Direction navigate(const MovableObject &object) const override;

};


#endif //PACMAN_ESCAPENAVIGATOR_H
