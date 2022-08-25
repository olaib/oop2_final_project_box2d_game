#pragma once
#include "Command.h"

class Exit : public Command
{
public:
	Exit();
	virtual bool execute(sf::RenderWindow&) override;
};