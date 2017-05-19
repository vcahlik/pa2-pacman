#ifndef PACMAN_ITEM_H
#define PACMAN_ITEM_H


#include "../GameObject.h"

class Game;

/**
 * @brief Object collectable by Player
 */
class Item
    : public GameObject
{
public:
    enum class State
    {
        Placed,
        Removed
    };

    explicit Item(const Position position, const double size, Game *game);

    virtual void performActions() override;

    const State getState() const;

protected:
    State state;

};


#endif //PACMAN_ITEM_H
