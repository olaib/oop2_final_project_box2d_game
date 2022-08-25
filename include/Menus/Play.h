#pragma once
#include "Command.h"

class Play : public Command 
{
public:
	Play();
	virtual bool execute(sf::RenderWindow&)override;
private:
};