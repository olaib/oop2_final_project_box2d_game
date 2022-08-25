#pragma once

#include "Command.h"


class Levels : public Command
{
public:
	Levels();
	
	virtual bool execute(sf::RenderWindow& window) override;
};