#ifndef PACMAN_CHERRY_H
#define PACMAN_CHERRY_H


#include "ScoreBonus.h"
#include "../../GameTimer.h"

class Cherry
    : public ScoreBonus
{
public:
    Cherry(const double posX, const double posY, Game *game);

    const bool performActions() override;

private:
    GameTimer timer;

};


#endif //PACMAN_CHERRY_H
