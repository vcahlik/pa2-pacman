#ifndef PACMAN_ENEMY_H
#define PACMAN_ENEMY_H


#include <memory>
#include "Model/GameObjects/MovableObject.h"
#include "Navigators/Navigator.h"

/**
 * @brief Object which (usually) kills the Player on collision
 */
class Enemy
        : public MovableObject
{
public:
    explicit Enemy(const Position position, const double speed, const double size, const NavigatorType navigatorType,
                   Game *game);

    virtual void performActions() override;

protected:
    void chooseDirection() override;

    const Navigator &getNavigator() const;

    /**
     * @brief Replaces the enemy's navigator with a different one
     * @param type
     */
    void setNavigator(const NavigatorType &type);

private:
    std::unique_ptr<Navigator> navigator; /**< @brief Enemy's active navigator to player */

};


#endif //PACMAN_ENEMY_H
