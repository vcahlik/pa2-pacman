#include "RandomNavigator.h"
#include "Utils.h"
#include "Model/GameObjects/MovableObject.h"

RandomNavigator::RandomNavigator(const MovableObject &owner, const GameMap &map)
        : Navigator(owner, map) {

}

const Direction RandomNavigator::navigate(const MovableObject &target) const {
    Direction direction;

    while (true) {
        direction = client.getRandomValidDirection();

        if (Utils::areOppositeDirections(direction, client.getDirection()) &&
            !client.isOnlyValidDirection(direction)) {
            continue;
        }

        return direction;
    }
}


