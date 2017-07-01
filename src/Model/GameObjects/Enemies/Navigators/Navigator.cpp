#include "Navigator.h"
#include "Model/GameObjects/MovableObject.h"

Navigator::Navigator(const MovableObject &owner, const GameMap &map)
        : client(owner),
          map(map) {

}
