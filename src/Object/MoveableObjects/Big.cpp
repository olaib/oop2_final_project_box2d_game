#include "Object/MoveableObjects/Big.h"

bool Big::m_registerIt = Factory<Player>::registerIt(Type::Big, [](const sf::Vector2f& position, b2World* world) ->
	std::unique_ptr<Player> { return std::make_unique<Big>(position, world); });

Big::Big(const sf::Vector2f& position, b2World* world) :
	Player(GameManager::objects::Big, Type::Big,
		position, world, { DOUBLE_RATIO, DOUBLE_RATIO  })
{
	setJumpVelocity(-7.8f);
}