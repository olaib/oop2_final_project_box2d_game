#include "Menus/Menu.h"
#include <iostream>
#include "GameManager.h"
#include "Controller.h"
#include "ResourcesTxtrs.h"

Menu::Menu(Menu_t menuType) :
	m_background(ResourcesTxtrs::getInstance().getSprite(Type::Background)),m_myType(menuType)
{
	m_background.setScale(WINDOW_DIMENSIONS.x / (m_background.getLocalBounds().width),
						  WINDOW_DIMENSIONS.y / (m_background.getLocalBounds().height));	
}

void Menu::run(sf::RenderWindow& window)
{
	auto command = 0;
	do 
	{
		checkIfLevelsMenu();
		draw(window);
		command = getCommandFromUser(window);
	} while (doCommand(command, window));
}

void Menu::checkIfLevelsMenu()
{
	if (m_myType == Menu_t::levelsMenu)
		for (auto& command : m_commands)
			if (command.first == Menu_t::level)
			{
				if (command.second->getNum() <= GameManager::instance().getMaxLevelUnlocked())
					command.second->setColor(PINKY_COLOR);
			}
}

void Menu::draw(sf::RenderWindow& window) const
{
	window.clear();
	window.draw(m_background);
	if (m_myType == Menu_t::MENU)
		GameManager::instance().drawTitle(window);
	for (const auto& command : m_commands)
	{
		command.second->draw(window);
	}

	GameManager::instance().draw(window);
	window.display();
}

int Menu::getCommandFromUser(sf::RenderWindow& window)
{
	for (auto event = sf::Event(); window.waitEvent(event);)
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			Controller::getController().clearBoard();
			window.close();
			exit (EXIT_SUCCESS);
		case sf::Event::MouseButtonReleased:
			const auto clickLocation = window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y });

			switch (event.mouseButton.button)
			{
			case sf::Mouse::Button::Left:
				GameManager::instance().checkButtons(clickLocation);
				const auto command = checkIfCommandSelected(clickLocation);
				if (command != NO_COMMAND_SELECTED)
				{
					return command;
				}
				break;
			}
		}
	}
	return NO_COMMAND_SELECTED;
}

bool Menu::doCommand(const int& command, sf::RenderWindow& window)
{
	return m_commands[command].second->execute(window);
}

int Menu::checkIfCommandSelected(const sf::Vector2f& mousePos)
{
	auto button = 0;
	for (const auto& command : m_commands)
	{
		if (command.second->isButtonPressed(mousePos))
		{
			return button;
		}
		button++;
	}
	return NO_COMMAND_SELECTED;
}

void Menu::add(Option&& command)
{
	m_commands.emplace_back(Option(std::move(command)));
}