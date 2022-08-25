#pragma once 
#include "Object/MoveableObjects/Player.h"
#include "Object/MoveableObjects/Box.h"
#include "Object/StaticObjects/Gate.h"

class Big : public Player
{
public:
	Big(const sf::Vector2f& position, b2World* world);
private:
	static bool m_registerIt;
};