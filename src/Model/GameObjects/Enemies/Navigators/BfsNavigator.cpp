#include <map>
#include <queue>
#include <set>
#include "BfsNavigator.h"
#include "../../MovableObject.h"

BfsNavigator::BfsNavigator(const MovableObject &owner, const GameMap &map)
        : Navigator(owner, map)
{

}

const std::set<std::pair<Coordinates, Direction>> BfsNavigator::getNeighborsWithDirections(const Coordinates &coord) const
{
    std::set<Direction> directions = {Direction::UP, Direction::DOWN, Direction::LEFT, Direction::RIGHT};
    std::set<std::pair<Coordinates, Direction>> validNeighborPairs;

    for (Direction direction : directions)
    {
        SquareType neighborType;

        try
        {
            neighborType = map.getSquareType(coord.relative(direction));
        } catch (const std::out_of_range &)
        {
            continue;
        }

        if (client.isCompatibleSquareType(neighborType))
        {
            validNeighborPairs.insert(std::make_pair(coord.relative(direction), direction));
        }
    }

    return validNeighborPairs;
}

const std::set<Coordinates> BfsNavigator::getNeighbors(const Coordinates &coord) const
{
    std::set<std::pair<Coordinates, Direction>> validNeighborPairs = getNeighborsWithDirections(coord);
    std::set<Coordinates> validNeighbors;

    for (const auto &neighborPair : validNeighborPairs)
    {
        validNeighbors.insert(neighborPair.first);
    }

    return validNeighbors;
}

const Direction BfsNavigator::navigate(const MovableObject &target) const
{
    Coordinates clientCoord = client.getPosition().toCoord();
    Coordinates destination = target.getPosition().toCoord();

    if (clientCoord == destination)
    {
        return client.getRandomValidDirection();
    }

    std::map<Coordinates, Direction> nonFreshWithDirections;
    std::queue<Coordinates> opened;

    nonFreshWithDirections[clientCoord] = Direction::NONE;

    // Push all neighbor nodes
    for (auto neighborPair : getNeighborsWithDirections(clientCoord))
    {
        if (neighborPair.first == destination)
        {
            return neighborPair.second;
        }
        opened.push(neighborPair.first);
        nonFreshWithDirections[neighborPair.first] = neighborPair.second;
    }

    while (!opened.empty())
    {
        //Expand

        Coordinates expanded = opened.front();
        opened.pop();

        for (Coordinates neighbor : getNeighbors(expanded))
        {
            if (nonFreshWithDirections.find(neighbor) != nonFreshWithDirections.end())
            {
                // Node is not fresh
                continue;
            }

            Direction bestDirection = nonFreshWithDirections[expanded];
            if (neighbor == destination)
            {
                return bestDirection;
            }

            nonFreshWithDirections[neighbor] = bestDirection;
            opened.push(neighbor);
        }
    }

    // No route found
    return client.getRandomValidDirection();
}
