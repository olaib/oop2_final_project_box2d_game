#include "Direction.h"

#include <stdexcept>

sf::Vector2f toVector(Direction dir)
{
    switch (dir)
    {
    case Direction::Up:
        return { 0, -1 };

    case Direction::Right:
        return { 1, 0 };

    case Direction::Left:
        return { -1, 0 };

    case Direction::Stay:
        return { 0, 0 };
    
    default:
        throw std::runtime_error("Unknown direction");
    }
}
