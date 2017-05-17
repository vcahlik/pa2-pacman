#ifndef PACMAN_BFSNAVIGATOR_H
#define PACMAN_BFSNAVIGATOR_H


#include <set>
#include "Navigator.h"

class BfsNavigator
    : public Navigator
{
public:
    explicit BfsNavigator(const MovableObject &client, const GameMap &map);

    const Direction navigate(const MovableObject &object) const override;

private:
    const std::set<std::pair<Coordinates, Direction>> getNeighborsWithDirections(const Coordinates &node) const;

    const std::set<Coordinates> getNeighbors(const Coordinates &node) const;


};


#endif //PACMAN_BFSNAVIGATOR_H
