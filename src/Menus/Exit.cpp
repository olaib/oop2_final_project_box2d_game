#include "Menus/Exit.h"
#include "ResourcesSounds.h"

Exit::Exit() :Command(Type::menuButton,
	sf::Vector2f(float(WINDOW_DIMENSIONS.x / 2), MENU_BUTTON_DIMENSIONS.y * 5)
	, std::string("Exit"), Fonts::Font1, MENU_BUTTON_DIMENSIONS) {}

bool Exit::execute(sf::RenderWindow&)
{
	ResourcesSounds::getInstance().stop(Sounds::Background);
	return EXIT;
}