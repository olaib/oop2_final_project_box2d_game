#include "Object/MoveableObjects/Small.h"

bool Small::m_registerIt = Factory<Player>::registerIt(Type::Small, [](const sf::Vector2f& position, b2World* world) ->
	std::unique_ptr<Player> { return std::make_unique<Small>(position, world); });

Small::Small(const sf::Vector2f& position, b2World* world):
	Player(GameManager::objects::Small, Type::Small, position, world, { STANDARD_RATIO, STANDARD_RATIO })
{
	setJumpVelocity(-8.f);
}