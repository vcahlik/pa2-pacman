#ifndef PACMAN_NAVIGATOR_H
#define PACMAN_NAVIGATOR_H


#include "Direction.h"
#include "Model/GameObjects/GameObject.h"

enum class NavigatorType
{
    Random,
    Bfs
};

/**
 * @brief Navigates the enemy in respect to some other object (usually to the Player)
 */
class Navigator
{
public:
    /**
     * @brief Constructor, assigns navigator to the owner
     * @param owner
     * @param map
     */
    explicit Navigator(const MovableObject &owner, const GameMap &map);

    /**
     * @brief Tells the owner where to go on intersections
     * @param target
     * @return
     */
    virtual const Direction navigate(const MovableObject &target) const = 0;

protected:
    const MovableObject &client;
    const GameMap &map;

};


#endif //PACMAN_NAVIGATOR_H
