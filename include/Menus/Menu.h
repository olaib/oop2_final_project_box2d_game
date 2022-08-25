#pragma once
#include "Command.h"
#include "SFML/Graphics.hpp"

using Option = std::pair<Menu_t, std::unique_ptr<Command>>;
//menu class for creating menus
class Menu
{
public:
	Menu(Menu_t);
	void run(sf::RenderWindow& );
	void checkIfLevelsMenu();
	void add(Option&&);
	auto getMyType()const { return m_myType; }
private:
	std::vector<Option>  m_commands;
	sf::Sprite           m_background;
	Menu_t               m_myType;
	//====================================================
	void draw(sf::RenderWindow& window) const;
	int getCommandFromUser(sf::RenderWindow& window);
	bool doCommand(const int& command, sf::RenderWindow& window);
	int checkIfCommandSelected(const sf::Vector2f& mousePos);
};



