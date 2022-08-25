#include "Menus/Restart.h"
#include "Controller.h"

Restart::Restart()
	:Command(Type::restartBtn,
			 sf::Vector2f(SMALL_BUTTON_DIMENSIONS.x * 1.5 + PAUSE_MENU_BUTTON_PADDING * 4,
						  MENU_DIMENSIONS.y * 1.5), std::string(),Fonts::Font1,
		                  SMALL_BUTTON_DIMENSIONS)
{}

bool Restart::execute(sf::RenderWindow&)
{
	Controller::getController().setIsRestart(true);
	return false;
}
