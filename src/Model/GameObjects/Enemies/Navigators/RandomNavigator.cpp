#include "RandomNavigator.h"
#include "../../../../Utils.h"
#include "../../MovableObject.h"

RandomNavigator::RandomNavigator(const MovableObject &client)
    : Navigator(client)
{

}

const Direction RandomNavigator::navigate(const MovableObject &object, const bool navigateCloser) const
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


