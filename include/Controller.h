#pragma once
#include <SFML/Graphics.hpp>
#include "Board.h"
#include "Menus/PauseMenu.h"

class Controller
{
public:
	enum class state {Exit,Running,noThing};
	static Controller& getController();
	bool run(sf::RenderWindow&, const int&);
	void clearBoard();
	auto setIsRestart(const bool& isRestart) { m_isRestart = isRestart; }
	auto setIsContinue(const bool& isContinue) { m_isContinue = isContinue; }
private:
	Controller();
	Board        m_board;
	PauseMenu    m_pauseMenu;
	sf::Sprite   m_backGround;
	GameStatus   m_gameStatus = GameStatus::Playing;
	bool         m_isContinue, m_isRestart;
	sf::Text     m_numOfLvl;
	sf::Sprite   m_key, m_arrow;
	int          m_lvlNum;
	//================ PRIVATE FUNCTIONS ===================
	void draw(sf::RenderWindow&)const;
	void update(sf::Clock&, const int&);
	void checkIfLvlWon(sf::RenderWindow&, sf::Clock&);
	void checkIflvlRestart(sf::RenderWindow&, sf::Clock&);
	state handleEvent(sf::RenderWindow& window);
	void loadLevel();
	void init();
};