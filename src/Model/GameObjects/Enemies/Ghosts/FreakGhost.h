#ifndef PACMAN_FREAKGHOST_H
#define PACMAN_FREAKGHOST_H


#include "Ghost.h"

class FreakGhost
    : public Ghost
{
public:
    FreakGhost(Game *game);

    void configureSpeed();

protected:
    void chooseDirection() override;

private:
    bool freakSpeed;

};


#endif //PACMAN_FREAKGHOST_H
