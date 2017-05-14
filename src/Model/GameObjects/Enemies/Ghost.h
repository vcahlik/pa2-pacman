#ifndef PACMAN_GHOST_H
#define PACMAN_GHOST_H


#include "Enemy.h"
#include "../../../View/Ncurses/Color.h"

class Ghost
    : public Enemy
{
public:
    explicit Ghost(const Position position, const double speed, Game *game);

    const Color getColor() const;

protected:
    virtual void navigate() override;

private:
    const Color getRandomColor() const;

    const Color color;

};


#endif //PACMAN_GHOST_H
