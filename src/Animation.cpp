#include "Animation.h"
#include <iostream>
#include "macros.hpp"
#include "ResourcesTxtrs.h"

Animation::Animation(const AnimationData& data, Direction dir, sf::Sprite& sprite, Type type)
    : m_data(data), m_dir(dir), m_sprite(sprite),m_animationTime(sf::seconds(ANIMATION_SPEED))
{
    m_sprite = ResourcesTxtrs::getInstance().getSprite(type);
    update();
}
//-----------------------------------------------------------------------------
void Animation::direction(Direction dir)
{
    if (m_dir == dir )
    {
        return;
    }
    m_index = 0;
    m_dir = dir;
    update();
}
//-----------------------------------------------------------------------------
void Animation::update(sf::Time delta)
{
    m_elapsed += delta;
    if (m_elapsed >= m_animationTime)
    {
        m_elapsed -= m_animationTime;
        ++m_index;

        m_index %= m_data.m_data.find(m_dir)->second.size();
        update();
    }
}
//-----------------------------------------------------------------------------
void Animation::setAnimationSpeed(const float& speed)
{
    m_animationTime = sf::seconds(speed);
}

//-----------------------------------------------------------------------------
void Animation::update()
{
    m_sprite.setTextureRect(m_data.m_data.find(m_dir)->second[m_index]);
    m_sprite.setOrigin( m_sprite.getTextureRect().width / 2.f,
                        m_sprite.getTextureRect().height / 2.f);
}