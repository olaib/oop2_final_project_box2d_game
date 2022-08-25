#pragma once
#include "StaticObject.h"

class BlockedTile : public StaticObject
{
public:
	BlockedTile(const sf::Vector2f& pos, b2World* world);
private:
	static bool m_registerIt;
};