#pragma once
#include "Object/MoveableObjects/MoveableObject.h"
#include "Animation.h"

class Player : public MoveableObject
{
public:
	Player(GameManager::objects animData, Type type, const sf::Vector2f& position, b2World* world,
		const sf::Vector2f& ratio);

	//===================== GET FUNCTIONS ==============
	bool getHasKey() const;
	auto getPosition()const { return m_sprite.getPosition(); }
	auto isAlive() const { return m_isAlive; }
	auto hasKeys()const { return m_keysCounter>0; }
	void incKeys() { m_keysCounter++; }
	void decKeys() { m_keysCounter--; }


	//==================== SET FUNCTIONS ===============
	void setHasKey(const bool& hasKey);
	void setJumpVelocity(const float& jumpVelocity) { m_jumpVelocity = jumpVelocity; }
	void setDirection();
	void setAlive(const bool& isAlive);

	//===================== OTHER FUNTIONS ==============
	void update(const sf::Time& deltaTime);

private:
	//===================== MEMBERS =====================
	bool           m_hasKey;
	float          m_jumpVelocity,
				   m_boostSpeed            = 3.f,
				   m_jumpElapsed = 0;
	static bool    m_isAlive;
	Animation      m_animation;
	Direction      m_dir                   = Direction::Stay;
	sf::Time       m_elapsed               = {},
		           m_deltaTime             = sf::seconds(0.1f);
	int            m_keysCounter;

	//===================== PRIVATE FUNCTIONS =============
	using MoveableObject::setBody;
	void setBody(b2World* world, Type type, const sf::Vector2f& position);
	void moveRight(const float& speed);
	void moveLeft(const float& speed);
	void jump();
	void move(const sf::Time& deltaTime);
	void setAnimationDirection(Direction dir, const float& animationSpeed);
};