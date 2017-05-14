#ifndef PACMAN_SCOREBONUS_H
#define PACMAN_SCOREBONUS_H


#include "Item.h"

class ScoreBonus
    : public Item
{
public:
    ScoreBonus(const Position position, const double size, const uint32_t scoreReward, Game *game);

    virtual const bool performActions() override;

private:
    const uint32_t scoreReward;

};


#endif //PACMAN_SCOREBONUS_H
