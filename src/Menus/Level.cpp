#include "Menus/Level.h"


Level::Level(const int& lvlNum) :Command(Type::menuButton,
	sf::Vector2f(SMALL_BUTTON_DIMENSIONS.x* (lvlNum - 1) + SMALL_BUTTON_DIMENSIONS.x / 2
		, LEVEL_MENU_DIMENSIONS.y / 2.f),
	std::string(std::to_string(lvlNum)), Fonts::Font2, SMALL_BUTTON_DIMENSIONS),
	m_lvlNum(lvlNum) 
{
	if(lvlNum == 1)
		setColor(PINKY_COLOR);
}

bool Level::execute(sf::RenderWindow& window)
{
	
	if (m_lvlNum <= GameManager::instance().getMaxLevelUnlocked())
	{
		setColor(PINKY_COLOR);
		while (Controller::getController().run(window, m_lvlNum));
	}
	return true;
}