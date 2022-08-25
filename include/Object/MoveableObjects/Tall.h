#pragma once
#include "Object/MoveableObjects/Player.h"

class Tall : public Player
{
public:
	Tall(const sf::Vector2f& position, b2World* world);
private:
	static bool m_registerIt;
};