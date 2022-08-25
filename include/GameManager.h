#pragma once
#include <SFML/Audio.hpp>
#include "macros.hpp"
#include "AnimationData.h"
#include <vector>
#include <iostream>

class GameManager
{
public:
	enum class objects : size_t
	{
		Big,
		Tall,
		Small,
		Max
	};
	enum class Messages {
		RestartLevel,
		EndGame,
		LevelUp,
		levelNumber
	};
	static GameManager& instance();
	GameManager(const GameManager&) = delete;
	GameManager& operator=(const GameManager&) = delete;

	//==============================================================
	const sf::Image& getCursorImg()const { return m_cursorImg; }
	AnimationData animationData(objects)const;


	sf::Text getText(Fonts font);

	void drawTitle(sf::RenderWindow& window)const;
	void draw(sf::RenderWindow& window)const;
	void checkButtons(const sf::Vector2f& pos);
	void setPlayersAtGate(const int& numOfPlayers);
	auto isLvlWon()const { return m_playersAtGate == 3; }
	auto isLvlLose()const { return m_isLvlLose; }
	void setLvlLose(const bool&& isLvlLose) { m_isLvlLose = isLvlLose; }
	void incPlayersAtGate() { m_playersAtGate++; }
	auto getMaxLevelUnlocked()const { return m_maxLvLUnlocked; }
	auto setMaxLevelUnlocked(const int& lvlNum) { m_maxLvLUnlocked = lvlNum; }
	void drawInstructions(sf::RenderWindow& window)const;
private:
	GameManager();
	void initButtons();
	//======================== MEMBERS =============================
	std::map<Fonts, sf::Font>                       m_fonts;
	sf::Image                                       m_cursorImg;
	std::vector<AnimationData>                      m_data;
	sf::Sprite                                      m_musicOff, m_musicOn,
                                                    m_title;
	sf::Text m_info;
	bool											m_isLvlLose;
	std::unordered_map<Messages, sf::Text>          m_messages;
	sf::Sprite                                      m_arrow, m_key,m_lvlNumber;
	int												m_playersAtGate, m_maxLvLUnlocked;
	//====================== INIT FUNCTIONS =========================
	void initFonts();
};
//=========================== GLOBAL FUNCTIONS =======================
void initText(sf::Text& text, const size_t& charSize, const std::string& str, Fonts font,
	const sf::Color& color, const sf::Vector2f& pos);