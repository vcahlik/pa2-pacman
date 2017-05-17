#include "RandomNavigator.h"
#include "../../../../Utils.h"
#include "../../MovableObject.h"

RandomNavigator::RandomNavigator(const MovableObject &client, const GameMap &map)
    : Navigator(client, map)
{

}

const Direction RandomNavigator::navigate(const MovableObject &object) const
{
    Direction direction;

    while (true)
    {
        direction = client.getRandomValidDirection();

        if (Utils::areOppositeDirections(direction, client.getDirection()) &&
            !client.isOnlyValidDirection(direction))
        {
            continue;
        }

        return direction;
    }
}


