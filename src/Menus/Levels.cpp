#include "Menus/Levels.h"
#include "Controller.h"


Levels::Levels()
	:Command(Type::levelsButton,
		sf::Vector2f(SMALL_BUTTON_DIMENSIONS.x / 2 + (PAUSE_MENU_BUTTON_PADDING * 3),
			MENU_DIMENSIONS.y + (MENU_DIMENSIONS.y / 2)), std::string(),
		Fonts::Font1, SMALL_BUTTON_DIMENSIONS)
{}

bool Levels::execute(sf::RenderWindow&)
{
	Controller::getController().setIsContinue(false);
	return false;
}