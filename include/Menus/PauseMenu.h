#include "Command.h"
#include "Menu.h"

class PauseMenu : public Command
{
public:
	PauseMenu();

	virtual bool execute(sf::RenderWindow& window) override;
};