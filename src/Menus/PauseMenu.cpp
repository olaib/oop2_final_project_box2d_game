#include "Menus/PauseMenu.h"
#include "Menus/Resume.h"
#include "Menus/Restart.h"
#include "Menus/Levels.h"
#include "Menus/Exit.h"

PauseMenu::PauseMenu() :Command(Type::pauseBtn,
	sf::Vector2f(WINDOW_DIMENSIONS.x - SMALL_BUTTON_DIMENSIONS.x / 2, SMALL_BUTTON_DIMENSIONS.y / 2),
	std::string(), Fonts::Font1, SMALL_BUTTON_DIMENSIONS)
{}

bool PauseMenu::execute(sf::RenderWindow& window)
{
	auto pauseMenu = Menu(Menu_t::pauseMenu);
	pauseMenu.add({ Menu_t::Levels,  std::make_unique<Levels>()  });
	pauseMenu.add({ Menu_t::Restart, std::make_unique<Restart>() });
	pauseMenu.add({ Menu_t::Resume,  std::make_unique<Resume>()  });
	pauseMenu.run(window);
	return true;
}
