#ifndef PACMAN_BFSNAVIGATOR_H
#define PACMAN_BFSNAVIGATOR_H


#include <set>
#include "Navigator.h"

/**
 * @brief Navigator navigating to the target using the heavy weight BFS algorithm
 */
class BfsNavigator
        : public Navigator
{
public:
    explicit BfsNavigator(const MovableObject &owner, const GameMap &map);

    const Direction navigate(const MovableObject &target) const override;

private:
    /**
     * @brief Returns valid neighboring Coordinates to the given node along with directions to them
     * @param node
     * @return
     */
    const std::set<std::pair<Coordinates, Direction>> getNeighborsWithDirections(const Coordinates &node) const;

    /**
     * @brief Returns valid neighboring Coordinates to the given node
     * @param node
     * @return
     */
    const std::set<Coordinates> getNeighbors(const Coordinates &node) const;

};


#endif //PACMAN_BFSNAVIGATOR_H
