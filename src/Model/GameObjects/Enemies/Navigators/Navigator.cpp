#include "Navigator.h"
#include "../../MovableObject.h"

Navigator::Navigator(const MovableObject &owner, const GameMap &map)
    : client(owner),
      map(map)
{

}
