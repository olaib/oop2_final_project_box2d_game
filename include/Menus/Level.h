#pragma once

#include "Command.h"
#include "Controller.h"

class Level : public Command
{
public:
	Level(const int& lvlNum);

	virtual bool execute(sf::RenderWindow& window) override;
	int getNum()const override{ return m_lvlNum; }
private:
	int m_lvlNum;
};