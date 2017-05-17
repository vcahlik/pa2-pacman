#ifndef PACMAN_SCOREBONUS_H
#define PACMAN_SCOREBONUS_H


#include "Item.h"

class ScoreBonus
    : public Item
{
public:
    explicit ScoreBonus(const Position position, const double size, const uint32_t scoreReward, Game *game);

    virtual void performActions() override;

private:
    const uint32_t scoreReward;

};


#endif //PACMAN_SCOREBONUS_H
