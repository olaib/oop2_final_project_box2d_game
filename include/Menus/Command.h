#pragma once
#include "SFML/Graphics.hpp"
#include "MenuButton.h"
#include "macros.hpp"


// this is command template class a design pattern for creating commands for menus
class Command
{
public:
	Command(Type, const sf::Vector2f& position, const std::string& string,
		    Fonts font, const sf::Vector2f& size);
	virtual int getNum()const { return -1; }
	virtual bool execute(sf::RenderWindow&) = 0;

	virtual void draw(sf::RenderWindow&)const;

	virtual bool isButtonPressed(const sf::Vector2f&);
	void setColor(const sf::Color& color) { m_menuButton.setColor(color); }
private:
	MenuButton m_menuButton;
};