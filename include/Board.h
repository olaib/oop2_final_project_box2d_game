#pragma once
#include <memory>
#include <fstream>
#include <unordered_map>
#include <iostream>
#include "MyListener.h"
//==========================================
#include "Object/MoveableObjects/Tall.h"
#include "Object/MoveableObjects/Small.h"
#include "Object/MoveableObjects/Big.h"
#include "Object/MoveableObjects/Box.h"
#include "Object/StaticObjects/BlockedTile.h"
#include "Object/StaticObjects/Gate.h"
#include "Object/StaticObjects/Key.h"
#include "Object/StaticObjects/Tile.h"
//==========================================
using MoveableObjectVec = std::vector <std::unique_ptr<MoveableObject>>;
using StaticObjectVec = std::vector <std::unique_ptr<StaticObject>>;
using PlayersVec = std::vector <std::unique_ptr<Player>>;
//==========================================

class Board
{
public:
	Board();
	//====================== GET FUNCTIONS =====================
	const sf::Vector2f& getCurrPlayerPos()const { return m_players[m_currPlayerIndx]->getPosition(); }
	auto isPlayerHasKey()const { return m_players[m_currPlayerIndx]->hasKeys(); }
	auto isAnyPlayerDied()const { return !m_players[m_currPlayerIndx]->isAlive(); }
	//====================== SET FUNCTIONS =====================
	//==========================================================
	void clearBoard();
	void loadLevel(const size_t& lvl);
	void update(const sf::Time& deltaTime, sf::Sprite& arrow);
	void draw(sf::RenderWindow& window) const;
	auto nextPlayer()
	{
		if(!m_players.empty())
			m_currPlayerIndx = (++m_currPlayerIndx) % m_players.size();
	}
private:
	//========================== MEMBERS ============================
	std::unique_ptr<b2World>                    m_world;
	StaticObjectVec                             m_staticObjects;
	MoveableObjectVec                           m_MoveableObjects;
	PlayersVec									m_players;
	MyListener                                  m_myListener;
	int								            m_currPlayerIndx;
	bool                                        m_isLvlWon;

	//=========================== PRIVATE FUCTIONS ====================
	void createObject(Type Type, const sf::Vector2f& pos);
	void checkIs2EraseObjects();
};
