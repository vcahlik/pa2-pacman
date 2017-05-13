#ifndef PACMAN_CHERRY_H
#define PACMAN_CHERRY_H


#include "ScoreBonus.h"
#include "../../GameTimer.h"
#include "../../GameMap.h"

class Cherry
    : public ScoreBonus
{
public:
    Cherry(Game *game);

    virtual const bool performActions() override;

private:
    void placeOnRandomPosition();

    const bool isCompatiblePosition(const uint32_t posX, const uint32_t posY) const;

    GameTimer timer;

};


#endif //PACMAN_CHERRY_H
