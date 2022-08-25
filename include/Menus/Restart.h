#pragma once

#include "Command.h"

class Restart : public Command
{
public:
	Restart();
	virtual bool execute(sf::RenderWindow& window) override;
};