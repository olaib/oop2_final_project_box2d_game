#pragma once
#include <SFML/Graphics.hpp>

#include "Direction.h"
#include "AnimationData.h"
#include "GameManager.h"

class Animation
{
public:
    Animation(const AnimationData& data, Direction dir, sf::Sprite& sprite, Type);
 
    void direction(Direction dir);
    void update(sf::Time delta);

    void setAnimationSpeed(const float& speed);
private:
    //=============== MEMBERS ==================
    sf::Sprite&            m_sprite;
    int                    m_index = 0;
    AnimationData          m_data;
    Direction              m_dir = Direction::Right;
    sf::Time               m_animationTime;
    sf::Time               m_elapsed = {};
    //=============== PRIVATE FUNTIONS =========
    void update();
};