#pragma once

#include <SFML/Graphics.hpp>

enum class Direction
{
    Right,
    Left,
    Stay,
    Up,
    Jump,
    Max,
};

enum class MoveType
{
    m_LeftRight,
    m_UpDown,
    None
};

sf::Vector2f toVector(Direction dir);
