#include "Object/Object.h"
#include "Object/StaticObjects/Tile.h"
#include "Object/MoveableObjects/Box.h"

Object::Object(Type texture, const sf::Vector2f& position, const sf::Vector2f& ratio) :
	m_sprite(ResourcesTxtrs::getInstance().getSprite(texture)),
	m_dimensions(CELL_DIMENSIONS.x * ratio.x, CELL_DIMENSIONS.y * ratio.y)
{
	m_sprite.setScale(m_dimensions.x / m_sprite.getLocalBounds().width, 
					  m_dimensions.y / m_sprite.getLocalBounds().height);

	m_sprite.setOrigin(m_sprite.getLocalBounds().width / 2,
					   m_sprite.getLocalBounds().height / 2);

	m_sprite.setPosition(position.x + m_sprite.getGlobalBounds().width / 2.f,
		                 position.y + m_sprite.getGlobalBounds().height / 2.f);
}

bool Object::isDisposed() const
{
	return m_isDisposed;
}

b2Body* Object::getBody() const
{
	return m_body;
}

sf::Vector2f Object::getSpritePosition() const
{
	return m_sprite.getPosition();
}

sf::FloatRect Object::getSpriteGlobalBounds() const
{
	return m_sprite.getGlobalBounds();
}

void Object::setDisposed()
{
	m_isDisposed = true;
}

//this function creates a body for static objects
void Object::setBody(b2World* world, b2BodyType type, const bool& isSensor, const bool& isInGroup)
{
	b2BodyDef bodyDef;
	bodyDef.type = type;
	const auto globalBounds = m_sprite.getGlobalBounds();
	const auto h = sf::Vector2f(globalBounds.width / 2, globalBounds.height / 2);
	bodyDef.position.Set(m_sprite.getPosition().x / BOX2D_SCALE,
						 m_sprite.getPosition().y / BOX2D_SCALE);
	bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(this);

	m_body = world->CreateBody(&bodyDef);
	b2FixtureDef fixtureDef;
	b2PolygonShape polygonShape;
	b2CircleShape circleShape;
	m_body->SetFixedRotation(true);
	if (!isInGroup)
	{
		polygonShape.SetAsBox(h.x / BOX2D_SCALE, h.y / BOX2D_SCALE);
		fixtureDef.shape = &polygonShape;
	}
	m_body->CreateFixture(&fixtureDef);
}

void Object::draw(sf::RenderWindow& window)
{
	if (typeid(*this) != typeid(Tile)) {
		auto position = b2Vec2();
		{
			position = m_body->GetPosition();
		}
		position *= BOX2D_SCALE;
		m_sprite.setPosition(position.x, position.y);
		m_sprite.setRotation(m_body->GetAngle() * RADIAN_TO_DEGREE);
	}
	window.draw(m_sprite);
}

//this function creates a body for a wall/floor
void Object::setBody(const sf::Vector2f& position, b2World* world)
{
	b2BodyDef bodyDef;
	bodyDef.type = b2BodyType::b2_staticBody;
	bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(this);
	m_body = world->CreateBody(&bodyDef);

	const auto size = sf::Vector2f(ResourcesTxtrs::getInstance().size(Type::Tile).x / 2,
								   ResourcesTxtrs::getInstance().size(Type::Tile).y / 2);

	b2Vec2 v0((position.x - size.x) / BOX2D_SCALE, (position.y + size.y + CELL_DIMENSIONS.y / 2) / BOX2D_SCALE),
		   v1(position.x / BOX2D_SCALE, (position.y + size.y) / BOX2D_SCALE),
		   v2((position.x + size.x) / BOX2D_SCALE, (position.y + size.y - CELL_DIMENSIONS.y / 2) / BOX2D_SCALE),
		   v3((position.x + size.x * 2) / BOX2D_SCALE, (position.y + size.y + CELL_DIMENSIONS.y / 2) / BOX2D_SCALE);

	b2EdgeShape edge1, edge2;
	edge1.SetOneSided(v0, v1, v2, v3);
	edge2.SetTwoSided(v1, v2);
	b2FixtureDef fixtureDef1, fixtureDef2;
	fixtureDef1.shape = &edge1;
	fixtureDef2.friction = 0.f;
	fixtureDef2.shape = &edge2;
	m_body->CreateFixture(&fixtureDef1);
	m_body->CreateFixture(&fixtureDef2);
}
