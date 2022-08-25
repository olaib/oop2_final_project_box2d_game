#pragma once

#include "Command.h"

class Resume : public Command
{
public:
	Resume();
	virtual bool execute(sf::RenderWindow&) override
	{
		return false;
	}
};