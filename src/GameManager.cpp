#include "GameManager.h"
#include "ResourcesTxtrs.h"
#include <exception>
#include <iostream>
#include "macros.hpp"
#include "ResourcesSounds.h"


namespace {
	bool buttonClicked(const sf::Sprite& button, const sf::Vector2f& pos)
	{
		return button.getGlobalBounds().contains(pos);
	}
	AnimationData big()
	{
		const auto textureSize = ResourcesTxtrs::getInstance().size(Type::Big);
		const auto size = sf::Vector2i((textureSize.x / 5.f), textureSize.y);
		const auto initSpace = sf::Vector2i(-size.x, 0);

		auto bigPlayerData = AnimationData{};
		auto currentStart = initSpace;

		auto nextStart = [&]()
		{
			currentStart.x += size.x;
			return currentStart;
		};

		for (int i = 0; i < 5; i++)
		{
			auto temp = nextStart();
			if (i == 0) {
				bigPlayerData.m_data[Direction::Stay].emplace_back(temp, size);
				bigPlayerData.m_data[Direction::Jump].emplace_back(temp, size);
			}
			bigPlayerData.m_data[Direction::Left].emplace_back(temp, size);
			bigPlayerData.m_data[Direction::Right].emplace_back(temp, size);
		}
		return bigPlayerData;
	}
	AnimationData tall()
	{
		const auto textureSize = ResourcesTxtrs::getInstance().size(Type::Tall);
		const auto size = sf::Vector2i((textureSize.x / 4.f), textureSize.y);
		const auto initSpace = sf::Vector2i(-size.x, 0);

		auto tallPlayerData = AnimationData{};
		auto currentStart = initSpace;

		auto nextStart = [&]()
		{
			currentStart.x += size.x;
			return currentStart;
		};

		for (int i = 0; i < 4; i++)
		{
			auto temp = nextStart();
			if (i == 0) {
				tallPlayerData.m_data[Direction::Stay].emplace_back(temp, size);
				tallPlayerData.m_data[Direction::Jump].emplace_back(temp, size);
			}
			tallPlayerData.m_data[Direction::Left].emplace_back(temp, size);
			tallPlayerData.m_data[Direction::Right].emplace_back(temp, size);
		}
		return tallPlayerData;
	}
	AnimationData small()
	{
		const auto textureSize = ResourcesTxtrs::getInstance().size(Type::Small);
		const auto size = sf::Vector2i((textureSize.x / 4.f), textureSize.y);
		const auto initSpace = sf::Vector2i(-size.x,0);

		auto smallPlayerData = AnimationData{};
		auto currentStart = initSpace;

		auto nextStart = [&]()
		{
			currentStart.x += size.x;
			return currentStart;
		};

		for (int i = 0; i < 4; i++)
		{
			auto temp = nextStart();
			if (i == 0) {
				smallPlayerData.m_data[Direction::Stay].emplace_back(temp, size);
				smallPlayerData.m_data[Direction::Jump].emplace_back(temp, size);
			}
			smallPlayerData.m_data[Direction::Left].emplace_back(temp, size);
			smallPlayerData.m_data[Direction::Right].emplace_back(temp, size);
		}
		return smallPlayerData;
	}
}

GameManager& GameManager::instance()
{
	static auto instance = GameManager();
	return instance;
}

sf::Text GameManager::getText(Fonts font)
{
	auto text = sf::Text();
	text.setFont(m_fonts.find(font)->second);
	return text;
}

void GameManager::drawTitle(sf::RenderWindow& window) const
{
	window.draw(m_title);
}

void GameManager::draw(sf::RenderWindow& window) const
{
	window.draw(m_musicOn);
	window.draw(m_musicOff);
}

void GameManager::checkButtons(const sf::Vector2f& pos)
{
	if (buttonClicked(m_musicOff, pos)) {
		ResourcesSounds::getInstance().setValume(0.f);
	}
	else if (buttonClicked(m_musicOn, pos)) {
		ResourcesSounds::getInstance().setValume(10.f);
	}
}

void GameManager::setPlayersAtGate(const int& numOfPlayers)
{
	m_playersAtGate = numOfPlayers;
}

void GameManager::drawInstructions(sf::RenderWindow& window) const
{
	window.draw(m_info);
}

GameManager::GameManager() :
	m_data(static_cast<size_t>(objects::Max)),
	m_musicOn(ResourcesTxtrs::getInstance().getSprite(Type::musicOn)),
	m_musicOff(ResourcesTxtrs::getInstance().getSprite(Type::musicOff)),
	m_playersAtGate(NO_PLAYERS), m_isLvlLose(false), m_maxLvLUnlocked(FIRST_LEVEL)
	,m_title(ResourcesTxtrs::getInstance().getSprite(Type::title))
{
	m_info.setFont(m_fonts[Fonts::Font3]);
	initButtons();
	initFonts();
	initText(m_info, CHAR_SIZE, INSTRUCTIONS, Fonts::Font4, PINKY_COLOR,
		sf::Vector2f(500, 690));

	m_title.setPosition(sf::Vector2f(300,75));
	m_title.setScale(DOUBLE_RATIO, DOUBLE_RATIO);
	m_data[static_cast<size_t>(objects::Big)] = big();
	m_data[static_cast<size_t>(objects::Tall)] = tall();
	m_data[static_cast<size_t>(objects::Small)] = small();

	m_cursorImg.create(30, 30);
	m_cursorImg.loadFromFile("resources/cursor.png");
}


void GameManager::initButtons()
{
	m_info.setPosition(200, 640);
	m_musicOn.setPosition(sf::Vector2f(100, 35));
	m_musicOff.setPosition(sf::Vector2f(m_musicOn.getPosition().x + 50, m_musicOn.getPosition().y ));
}

AnimationData GameManager::animationData(objects object)const
{
	return m_data[static_cast<size_t>(object)];
}

void GameManager::initFonts()
{
	if (!m_fonts[Fonts::Font1].loadFromFile("resources/font1.ttf") ||
		!m_fonts[Fonts::Font2].loadFromFile("resources/font2.ttf") ||
		!m_fonts[Fonts::Font3].loadFromFile("resources/font3.ttf") ||
		!m_fonts[Fonts::Font4].loadFromFile("resources/font4.ttf") ||
		!m_fonts[Fonts::Font5].loadFromFile("C:/Windows/Fonts/COOPBL.ttf")
		)
		throw  std::runtime_error("Can't load one of fonts file!");
}

void initText(sf::Text& text, const size_t& charSize, const std::string& str, Fonts font, 
	const sf::Color& color, const sf::Vector2f& pos)
{
	text.setString(str);
	text.setPosition(pos);
	text.setFillColor(color);
	text.setCharacterSize(charSize);
	text.setOrigin(text.getGlobalBounds().width / 2.f
				 , text.getGlobalBounds().height / 2.f);
	text.setOutlineColor(sf::Color::Black);
	text.setOutlineThickness(2.f);
}
