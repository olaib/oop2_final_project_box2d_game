#include "Menus/Resume.h"

Resume::Resume() :Command(Type::resumeBtn,
		sf::Vector2f(SMALL_BUTTON_DIMENSIONS.x * 1.5 + PAUSE_MENU_BUTTON_PADDING * 5,
			MENU_DIMENSIONS.y * 1.5), std::string(), Fonts::Font1,
		SMALL_BUTTON_DIMENSIONS)
{}