#ifndef PACMAN_NORMALGHOST_H
#define PACMAN_NORMALGHOST_H


#include "Ghost.h"

/**
 * @brief A simple ghost navigating almost randomly
 */
class NormalGhost
        : public Ghost
{
public:
    NormalGhost(Game *game);
};


#endif //PACMAN_NORMALGHOST_H
