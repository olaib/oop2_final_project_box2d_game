#pragma once
#include "box2d/box2d.h"
#include "macros.hpp"
#include "Factory.h"
#include "ResourcesTxtrs.h"
#include "ResourcesSounds.h"

class Object 
{
public:
	Object() = default;
	Object(Type texture, const sf::Vector2f& position, const sf::Vector2f& ratio = {1,1});
	virtual ~Object() = default;

	//=============== GET FUNCTIONS ===============
	virtual bool isDisposed() const;
	b2Body* getBody() const;
	sf::Vector2f getSpritePosition() const;
	sf::FloatRect getSpriteGlobalBounds() const;

	//=============== SET FUNTIONS ================
	virtual void setDisposed();
	virtual void setBody(b2World*, b2BodyType, const bool&, const bool&);

	//=============== OTHER FUNCTIONS =============
	virtual void draw(sf::RenderWindow& window);
	void setBody(const sf::Vector2f& position, b2World* world);
//========================== MEMBERS ==========================
protected:
	sf::Sprite     m_sprite;
	b2Body*        m_body = nullptr;
	
private:
	bool           m_isDisposed = false;
	sf::Vector2f   m_dimensions;
};