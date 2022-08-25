#include "Object\MoveableObjects\Player.h"
#include <iostream>

bool Player::m_isAlive = true;

namespace 
{
	bool isKeyPressed(sf::Keyboard::Key key)
	{
		return sf::Keyboard::isKeyPressed(key);
	}
}
Player::Player(GameManager::objects animData, Type type, const sf::Vector2f& position, b2World* world, const sf::Vector2f& ratio) :
	m_animation(GameManager::instance().animationData(animData), Direction::Stay, m_sprite, type),
	m_hasKey(false), m_keysCounter(RESET)
{
	const auto dimensions = sf::Vector2f(CELL_DIMENSIONS.x * ratio.x, CELL_DIMENSIONS.y* ratio.y);
	m_sprite.setScale(dimensions.x / m_sprite.getLocalBounds().width, dimensions.y / m_sprite.getLocalBounds().height);

	m_sprite.setPosition(position.x + m_sprite.getGlobalBounds().width / 2,
						 position.y + m_sprite.getGlobalBounds().height / 2);

	setBody(world, type, position);
	
	setAlive(true);
}

void Player::setBody(b2World* world, Type type, const sf::Vector2f& position)
{
	const auto globalBounds = m_sprite.getGlobalBounds();
	const auto h = sf::Vector2f(globalBounds.width/2 , globalBounds.height/2);

	b2BodyDef bodyDef;
	b2FixtureDef fixtureDef;
	b2PolygonShape box;

	box.SetAsBox(h.x / BOX2D_SCALE, h.y/ BOX2D_SCALE);
	bodyDef.type = b2_dynamicBody;
	bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(this);
	bodyDef.position = b2Vec2((position.x + h.x ) * BOX2D_SCALE, (position.y + h.y) * BOX2D_SCALE);
	m_body = world->CreateBody(&bodyDef);
	fixtureDef.shape = &box;
	fixtureDef.friction = 1.f;
	fixtureDef.filter.groupIndex = -1;
	auto myMass = 1;     // mass for small
	if (type == Type::Big) { myMass = 10; }
	else if (type == Type::Tall) { myMass = 2; }
	fixtureDef.density = myMass;

	m_body->CreateFixture(&fixtureDef);
	m_body->SetFixedRotation(true);

	b2Vec2 startPos(m_sprite.getPosition().x / BOX2D_SCALE,
					m_sprite.getPosition().y / BOX2D_SCALE);
	m_body->SetTransform(startPos, 0);
}

void Player::setHasKey(const bool& hasKey)
{
	m_hasKey = hasKey;
}

bool Player::getHasKey()const
{
	return m_hasKey;
}

void Player::setDirection()
{
	m_elapsed = m_elapsed.Zero;
	m_dir = Direction::Stay;
}

void Player::setAlive(const bool& isAlive)
{
	m_isAlive = isAlive;
}

void Player::move(const sf::Time& deltaTime)
{
	m_elapsed += deltaTime;
	m_jumpElapsed += deltaTime.asSeconds();
	static const auto speed = 3.f;
	jump();
	moveLeft(speed);
	moveRight(speed);
	if (m_body->GetLinearVelocity().y < 0.1f && m_body->GetLinearVelocity().x != 0)
		m_boostSpeed = 0.3f;
	if (abs(m_body->GetLinearVelocity().x) <= 1 && m_body->GetLinearVelocity().y == 0)
		setAnimationDirection(Direction::Stay, 0.3f);
}

void Player::setAnimationDirection(Direction dir, const float& animationSpeed)
{
	if (m_dir != dir)
	{
		if (dir == Direction::Left)
		{
			m_sprite.setScale(-1 * abs(m_sprite.getScale().x), m_sprite.getScale().y);
		}
		else if (dir == Direction::Right)
		{
			m_sprite.setScale(abs(m_sprite.getScale().x), m_sprite.getScale().y);
		}
	}
	m_dir = dir;
	m_animation.direction(dir);
	m_animation.setAnimationSpeed(animationSpeed);
}

void Player::update(const sf::Time& deltaTime)
{
	move(deltaTime);
	m_animation.update(deltaTime);
}

void Player::moveRight(const float& speed)
{
	if (isKeyPressed(sf::Keyboard::Right) || isKeyPressed(sf::Keyboard::D))
	{
		m_body->SetLinearVelocity({ speed, m_body->GetLinearVelocity().y });
		if (m_body->GetLinearVelocity().y == 0 && m_boostSpeed == 0.3f)
			setAnimationDirection(Direction::Right, 0.1f);
	}
}

void Player::moveLeft(const float& speed)
{
	if (isKeyPressed(sf::Keyboard::Left) || isKeyPressed(sf::Keyboard::Key::A))
	{
		m_body->SetLinearVelocity({ -speed, m_body->GetLinearVelocity().y });
		if (m_body->GetLinearVelocity().y == 0 && m_boostSpeed == 0.3f)
			setAnimationDirection(Direction::Left, 0.1f);
	}
}

void Player::jump()
{
	if ((isKeyPressed(sf::Keyboard::Up)|| isKeyPressed(sf::Keyboard::Key::W)) 
		&& m_body->GetLinearVelocity().y == 0 && m_jumpElapsed>1.1f)
	{
		ResourcesSounds::getInstance().play(Sounds::Jump);
		m_body->SetLinearVelocity({ m_body->GetLinearVelocity().x, m_jumpVelocity });
		setAnimationDirection(Direction::Jump, 0.03f);
		m_jumpElapsed = 0;
	}
}