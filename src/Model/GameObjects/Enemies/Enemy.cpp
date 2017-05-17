#include <cstdlib>
#include <stdexcept>
#include "Enemy.h"
#include "../../../Utils.h"
#include "../Items/Item.h"
#include "../../Game.h"
#include "Navigators/RandomNavigator.h"
#include "Navigators/BfsNavigator.h"
#include "Navigators/EscapeNavigator.h"

Enemy::Enemy(const Position position, const double speed, const double size, const NavigatorType navigatorType, Game *game)
        : MovableObject(position, speed, size, game),
          invincible(true)
{
    setNavigator(navigatorType);
}

void Enemy::chooseDirection()
{
    if (!position.isOnCoordinateGrid())
    {
        return;
    }

    if (!isValidDirection(direction) || game->getMap().isIntersectionForObject(position.toCoord(), *this))
    {
        direction = navigator->navigate(game->getPlayer());
    }
}

void Enemy::performActions()
{
    MovableObject::performActions();

    if (isCollision(game->getPlayer()))
    {
        game->getPlayer().die();
    }
}

const Navigator &Enemy::getNavigator() const
{
    return *navigator;
}

void Enemy::setNavigator(const NavigatorType &type)
{
    switch (type)
    {
        case NavigatorType::Random:
            // TODO understand move assignments
            navigator = std::make_unique<RandomNavigator>(*this, game->getMap());
            //navigator.reset(new RandomNavigator(*this));
            break;
        case NavigatorType::Bfs:
            // TODO understand move assignments
            navigator = std::make_unique<BfsNavigator>(*this, game->getMap());
            //navigator.reset(new Bfs(*this));
            break;
        case NavigatorType::Escape:
            // TODO understand move assignments
            navigator = std::make_unique<EscapeNavigator>(*this, game->getMap());
            //navigator.reset(new Bfs(*this));
            break;
    }
}
