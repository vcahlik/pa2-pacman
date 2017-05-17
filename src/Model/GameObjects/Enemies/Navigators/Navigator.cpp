#include "Navigator.h"
#include "../../MovableObject.h"

Navigator::Navigator(const MovableObject &client, const GameMap &map)
    : client(client),
      map(map)
{

}
