#ifndef PACMAN_AGGRESSIVEGHOST_H
#define PACMAN_AGGRESSIVEGHOST_H


#include "Ghost.h"

class AggressiveGhost
    : public Ghost
{
public:
    AggressiveGhost(const Position &position, const double speed, Game *game);

};


#endif //PACMAN_AGGRESSIVEGHOST_H
