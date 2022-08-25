#pragma once
#include "Object/MoveableObjects/MoveableObject.h"

class Box : public MoveableObject
{
public:
	Box(const sf::Vector2f& position, b2World* world);
private:
	static bool m_registerIt;
};