#include "Menus/MenuButton.h"
#include "GameManager.h"
#include "ResourcesTxtrs.h"

MenuButton::MenuButton(Type button, Fonts font, const sf::Vector2f& position, const sf::Vector2f& size, const std::string& string)
	: m_sprite(ResourcesTxtrs::getInstance().getSprite(button)),
	m_text(GameManager::instance().getText(Fonts::Font5))
{
	m_sprite.setScale(size.x / (m_sprite.getLocalBounds().width),
		size.y / (m_sprite.getLocalBounds().height));
	m_sprite.setOrigin(m_sprite.getLocalBounds().width / 2, m_sprite.getLocalBounds().height / 2);
	m_sprite.setPosition(position);

	m_text.setString(string);
	m_text.setCharacterSize(70);
	m_text.setFillColor(sf::Color::White);
	m_text.setOrigin(m_text.getLocalBounds().width / 2, m_text.getLocalBounds().height / 2);
	m_text.setPosition(position.x, position.y - 18);
}

void MenuButton::draw(sf::RenderWindow& window) const
{
	window.draw(m_sprite);
	if (m_text.getString()!= std::string())
	{
		window.draw(m_text);
	}
}

bool MenuButton::clicked(const sf::Vector2f& mousePos) const
{
	return m_sprite.getGlobalBounds().contains(mousePos);
}