#include "Object/MoveableObjects/Tall.h"

bool Tall::m_registerIt = Factory<Player>::registerIt(Type::Tall, [](const sf::Vector2f& position, b2World* world) ->
	std::unique_ptr<Player> { return std::make_unique<Tall>(position, world); });

Tall::Tall(const sf::Vector2f& position, b2World* world):
	Player(GameManager::objects::Tall, Type::Tall, position, world,  { STANDARD_RATIO , DOUBLE_RATIO*0.9 })
{
	setJumpVelocity(-9.f);
}