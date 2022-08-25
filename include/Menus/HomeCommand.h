#pragma once

#include "Command.h"


class HomeCommand : public Command
{
public:
	HomeCommand()
		:Command(Type::HomeBtn,
			sf::Vector2f(WINDOW_DIMENSIONS.x - SMALL_BUTTON_DIMENSIONS.x / 2,SMALL_BUTTON_DIMENSIONS.y / 2),
			std::string(), Fonts::Font1, SMALL_BUTTON_DIMENSIONS) {}

	virtual bool execute(sf::RenderWindow&) override
	{
		return EXIT;
	}
};