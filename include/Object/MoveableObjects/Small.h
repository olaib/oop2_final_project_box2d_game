#pragma once
#include "Object/MoveableObjects/Player.h"

class Small : public Player
{
public:
	Small(const sf::Vector2f& position, b2World* world);
private:
	static bool m_registerIt;
};