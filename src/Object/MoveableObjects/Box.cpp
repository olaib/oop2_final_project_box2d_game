#include "Object/MoveableObjects/Box.h"

bool Box::m_registerIt = Factory<MoveableObject>::registerIt(Type::Box, [](const sf::Vector2f& position, b2World* world) ->
	std::unique_ptr<MoveableObject> { return std::make_unique<Box>(position, world); });

Box::Box(const sf::Vector2f& position , b2World* world) :
	MoveableObject(Type::Box, position, { DOUBLE_RATIO,DOUBLE_RATIO })
{
	auto x = m_sprite.getGlobalBounds().width/2 ;
	auto y = m_sprite.getGlobalBounds().height/2 ;

	b2BodyDef bodyDef;
	b2FixtureDef fixtureDef;
	b2PolygonShape box;

	box.SetAsBox(x / BOX2D_SCALE, y / BOX2D_SCALE);
	bodyDef.type = b2_dynamicBody;
	m_body = world->CreateBody(&bodyDef);
	fixtureDef.shape = &box;
	fixtureDef.density = 150.f;
	fixtureDef.friction = 1.5f;
	m_body->CreateFixture(&fixtureDef);
	m_body->SetFixedRotation(true);

	b2Vec2 startPos(m_sprite.getPosition().x / BOX2D_SCALE,
			        m_sprite.getPosition().y / BOX2D_SCALE);
	m_body->SetTransform(startPos, 0);
	bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(this);
}