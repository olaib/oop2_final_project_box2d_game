#include "Menus/Play.h"
#include "Menus/Menu.h"
#include "Menus/Level.h"
#include "Menus/HomeCommand.h"


Play::Play() :Command(Type::menuButton,
	sf::Vector2f(float(WINDOW_DIMENSIONS.x / 2), MENU_DIMENSIONS.y * 3.2f)
	, std::string("Play"), Fonts::Font1, MENU_BUTTON_DIMENSIONS) {}

bool Play::execute(sf::RenderWindow& window)
{
	auto levelMenu = Menu(Menu_t::levelsMenu);

	for (auto level = 1; level <= NUM_OF_LEVELS; ++level)
	{
		levelMenu.add({ Menu_t::level, std::make_unique<Level>(level) });
	}

	levelMenu.add({ Menu_t::homeMenu, std::make_unique<HomeCommand>() });

	levelMenu.run(window);

	return true;
}
