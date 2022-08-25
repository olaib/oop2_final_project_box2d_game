#pragma once
#include "macros.hpp"

class MenuButton
{
public:
	MenuButton(Type button, Fonts font, const sf::Vector2f& position,
		const sf::Vector2f& size, const std::string& string);

	void draw(sf::RenderWindow&) const;
	bool clicked(const sf::Vector2f&)const;
	void setColor(const sf::Color& color) { m_sprite.setColor(PINKY_COLOR); }
	const std::string& getString()const { return m_text.getString(); }
private:
	//================== MEMBERS =======================
	sf::Sprite    m_sprite;
	sf::Text      m_text;
};