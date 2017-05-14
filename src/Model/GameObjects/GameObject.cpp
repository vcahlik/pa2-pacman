#include "GameObject.h"

GameObject::GameObject(const Position position, const double size, Game *game)
    : game(game),
      size(size)
{
    this->position = getCenteredPosition(position);
}

const bool GameObject::isCompatibleSquareType(const SquareType squareType) const
{
    return squareType == SquareType::Space;
}

const bool GameObject::isCollision(const GameObject &other) const
{
    return (this->position.x + this->size > other.position.x &&
            this->position.x < other.position.x + other.size &&
            this->position.y + this->size > other.position.y &&
            this->position.y < other.position.y + other.size);
}

const Position &GameObject::getPosition() const
{
    return position;
}

const Position GameObject::getCenteredPosition(const Position rawPosition) const
{
    return Position(rawPosition.x + (1 - size) / 2,
                    rawPosition.y + (1 - size) / 2);
}
