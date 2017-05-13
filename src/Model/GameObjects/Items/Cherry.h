#ifndef PACMAN_CHERRY_H
#define PACMAN_CHERRY_H


#include "ScoreBonus.h"

class Cherry
    : public ScoreBonus
{
public:
    Cherry(const double posX, const double posY, Game *game);

};


#endif //PACMAN_CHERRY_H
