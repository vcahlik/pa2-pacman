#ifndef PACMAN_FREAKGHOST_H
#define PACMAN_FREAKGHOST_H


#include "Ghost.h"

/**
 * @brief Randomly moving ghost which sometimes starts moving rapidly for a short time
 *
 * Can speed only in chase mode.
 */
class FreakGhost
    : public Ghost
{
public:
    FreakGhost(Game *game);

    /**
     * @brief Randomly decides whether player will change speed
     */
    void configureSpeed();

protected:
    void chooseDirection() override;

private:
    bool freakSpeed;

};


#endif //PACMAN_FREAKGHOST_H
