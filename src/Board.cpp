#include "Board.h"
#include <sstream>
#include "GameManager.h"

const auto GRAVITY = b2Vec2{ 0.0f, 15.f };

namespace {
	Type char2Type(const char& _ch)
	{
		const auto _char2Type = std::unordered_map<char, Type>
			({
				{'S' ,Type::Small       },
				{'B' ,Type::Big         },
				{'T' ,Type::Tall        },
				{'-' ,Type::Tile        },
				{'?' ,Type::BlockedTile },
				{'*' ,Type::Thorn       },
				{'K' ,Type::Key         },
				{'@' ,Type::Gate        },
				{'#' ,Type::Box		    },
				});
		try
		{
			return _char2Type.at(_ch);
		}
		catch (const std::out_of_range&)
		{
			throw(std::exception("Invalid input!"));
		}
	}
	sf::Vector2f getPosition(const size_t& row, const size_t& col)
	{
		return { CELL_DIMENSIONS.x * col , CELL_DIMENSIONS.y * row };
	}
}

Board::Board() :
	m_world(std::make_unique<b2World>(GRAVITY)), m_isLvlWon(false), m_currPlayerIndx(RESET)
{
	m_world->SetContactListener(&m_myListener);
}

void Board::checkIs2EraseObjects()
{
	for (const auto& staticObj : m_staticObjects)
		if(staticObj->isDisposed())
			m_world->DestroyBody(staticObj->getBody());

	std::erase_if(m_staticObjects, [](const auto& staticObject)
		{
			return staticObject->isDisposed();
		});
	if (std::any_of(m_players.cbegin(), m_players.cend(), [](const auto& player) { return !player->isAlive();}))
		GameManager::instance().setLvlLose(true);

	if (!m_players.empty()){
		if (m_players[m_currPlayerIndx]->isDisposed()) {
			m_world->DestroyBody(m_players[m_currPlayerIndx]->getBody());
			m_players.erase(m_players.begin() + m_currPlayerIndx);
			nextPlayer();
		}
	}
}

void Board::update(const sf::Time& deltaTime, sf::Sprite& arrow)
{
	m_world->Step(TIME_STEP, 9, 3);
	checkIs2EraseObjects();
	if (GameManager::instance().isLvlWon())
		return;

	m_players[m_currPlayerIndx]->update(deltaTime);

	arrow.setPosition(getCurrPlayerPos().x, getCurrPlayerPos().y - 60);
}

void Board::draw(sf::RenderWindow& window) const
{
	for (const auto& staticObj : m_staticObjects)
		staticObj->draw(window);

	for (const auto& moveableObj : m_MoveableObjects)
		moveableObj->draw(window);

	for (const auto& player : m_players)
		player->draw(window);
}

void Board::loadLevel(const size_t& lvl)
{
	const auto level = "resources/" + std::to_string(lvl);
	auto lvlFile = std::ifstream(level + ".txt");
	char character;
	
	if (!lvlFile)         
	{ 
		throw std::ifstream::failure("Could not open lvl file!");
	}
	if (lvlFile.fail())   
	{ 
		throw std::out_of_range("Cannot find file: " + std::to_string(lvl));
	}
	for (size_t row = 0; row < BOARD_HEIGHT; ++row)
	{
		for (size_t col = 0; col < BOARD_WIDTH; ++col)
		{
			character = lvlFile.get();
			if (character != EmptyTile)
				createObject(char2Type(character), getPosition(row, col));
		}
		lvlFile.get();
	}
	lvlFile.close();
}

void Board::createObject(Type type,const sf::Vector2f& pos)
{
	//check if it is a static object
	if (auto object1 = Factory<StaticObject>::create(type, pos, m_world.get()))
	{
		m_staticObjects.emplace_back(std::move(std::unique_ptr<StaticObject>(std::move(object1))));
		return;
	}
	//check if it is a moveable object
	if (auto object2 = Factory<MoveableObject>::create(type, pos, m_world.get()))
	{
		m_MoveableObjects.emplace_back(std::unique_ptr<MoveableObject>(std::move(object2)));
		return;
	}
	//check if it is a player
	if (auto object3 = Factory<Player>::create(type, pos, m_world.get()))
	{
		m_players.emplace_back(std::unique_ptr<Player>(std::move(object3)));
		return;
	}
	//if unknown type
	throw std::invalid_argument("Invalid input's type!");
}

void Board::clearBoard()
{
	m_currPlayerIndx = RESET;
	GameManager::instance().setPlayersAtGate(NO_PLAYERS);// Represents if the level ends(victory)
	GameManager::instance().setLvlLose(false);
	// destroy bodies in box2d
	for (const auto& staticObject : m_staticObjects)
		m_world->DestroyBody(staticObject->getBody());

	for (const auto& moveableObject : m_MoveableObjects)
		m_world->DestroyBody(moveableObject->getBody());

	for(const auto& player : m_players)
		m_world->DestroyBody(player->getBody());
	
	m_staticObjects.clear();
	m_MoveableObjects.clear();
	m_players.clear();
}
