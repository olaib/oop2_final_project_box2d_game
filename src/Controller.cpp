#include "Controller.h"
#include "ResourcesTxtrs.h"

namespace {
	void setSprites(const sf::Vector2f& pos,sf::Sprite& sprite) 
	{
		sprite.setOrigin(sprite.getGlobalBounds().width / 2, 
						 sprite.getGlobalBounds().height / 2);
		sprite.setPosition(pos);
	}
	void printMessage(sf::RenderWindow& window, const sf::Clock& clock, sf::Sprite& image, const float& time)
	{
		auto endTime = clock.getElapsedTime().asSeconds();
		setSprites(sf::Vector2f(WINDOW_DIMENSIONS.x / 2, WINDOW_DIMENSIONS.y / 2), image);
		window.draw(image);
		window.display();
		while (clock.getElapsedTime().asSeconds() < endTime + time);
	}
	void drawEndGame(sf::RenderWindow& window, const sf::Clock& clock)
	{
		ResourcesSounds::getInstance().play(Sounds::endGame);
		static auto gameOver = ResourcesTxtrs::getInstance().getSprite(Type::GameOver);
		printMessage(window, clock, gameOver, 15.f);
		ResourcesSounds::getInstance().stop(Sounds::endGame);
	}
	bool isKeyPressed(sf::Keyboard::Key key)
	{
		return sf::Keyboard::isKeyPressed(key);
	}
}

Controller::Controller() : m_isContinue(true), m_isRestart(false),
	m_board(), m_pauseMenu({}), m_numOfLvl(GameManager::instance().getText(Fonts::Font2)),
	m_key(ResourcesTxtrs::getInstance().getSprite(Type::Key)),
	m_arrow(ResourcesTxtrs::getInstance().getSprite(Type::arrow))
	,m_backGround(ResourcesTxtrs::getInstance().getSprite(Type::Background2))
{
	init();
}

Controller& Controller::getController()
{
	static Controller controller;
	return controller;
}

bool Controller::run(sf::RenderWindow& window, const int& lvlNumber)
{
	m_board.loadLevel(lvlNumber);
	m_numOfLvl.setString(LEVEL + std::to_string(lvlNumber));
	m_lvlNum = lvlNumber;
	static auto clock = sf::Clock();
	clock.restart();
	do
	{
		draw(window);
		checkIflvlRestart(window, clock);
		checkIfLvlWon(window, clock);
		if (m_lvlNum > NUM_OF_LEVELS) {
			return EXIT;
		}
		update(clock , lvlNumber);
		const auto _state = handleEvent(window);
		if (_state == state::Exit)
			return EXIT;
		
	} while (RUNNING);

	return EXIT;
}

void Controller::clearBoard()
{
	m_board.clearBoard();
}

void Controller::draw(sf::RenderWindow& window)const
{
	window.clear(sf::Color::White);
	window.draw(m_backGround);

	m_board.draw(window);
	window.draw(m_numOfLvl);

	if (!GameManager::instance().isLvlWon()) {
		if (m_board.isPlayerHasKey())
			window.draw(m_key);
	}
	window.draw(m_arrow);

	m_pauseMenu.draw(window);
	if (m_lvlNum == 1) {

		GameManager::instance().drawInstructions(window);
	}
	window.display();
}

void Controller::update(sf::Clock& clock, const int& lvlNumber)
{
	const auto deltaTime = clock.restart();

	m_board.update(deltaTime, m_arrow);
}

Controller::state Controller::handleEvent(sf::RenderWindow& window)
{
	for (auto event = sf::Event(); window.pollEvent(event);)
	{
		if (isKeyPressed(sf::Keyboard::Down) || isKeyPressed(sf::Keyboard::S))
			m_board.nextPlayer();

		switch (event.type)
		{
		case sf::Event::MouseButtonReleased:
			if (event.mouseButton.button == sf::Mouse::Button::Left)
				if (m_pauseMenu.isButtonPressed(window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y })))
				{ //check pause menu buttons
					m_pauseMenu.execute(window);
					if (!m_isContinue)
					{
						m_board.clearBoard();
						m_isContinue = true;
						return state::Exit;
					}
					if (m_isRestart)
					{
						m_isRestart = false;
						loadLevel();
						return state::Running;
					}
				}
		}
	}
	return  state::noThing;
}

void Controller::checkIfLvlWon(sf::RenderWindow& window, sf::Clock& clock)
{
	if (!GameManager::instance().isLvlWon())
		return;
	m_lvlNum++;
	//if last level in levels menu 
	if (m_lvlNum > NUM_OF_LEVELS)
	{
		drawEndGame(window, clock);
		return;
	}
	m_numOfLvl.setString(LEVEL + std::to_string(m_lvlNum));
	//update max unlocked level num
	if (GameManager::instance().getMaxLevelUnlocked() < m_lvlNum)
		GameManager::instance().setMaxLevelUnlocked(m_lvlNum);

	ResourcesSounds::getInstance().play(Sounds::win);

	auto endTime = clock.getElapsedTime().asSeconds();

	static auto lvlMsg = GameManager::instance().getText(Fonts::Font4);
	initText(lvlMsg, 200.f, LEVEL + std::to_string(m_lvlNum), Fonts::Font4, PINKY_COLOR,
		sf::Vector2f(WINDOW_DIMENSIONS.x / 2, WINDOW_DIMENSIONS.y / 2 - 50));

	window.draw(lvlMsg);
	window.display();
	while (clock.getElapsedTime().asSeconds() < endTime + 3.f);
	loadLevel();
}

void Controller::loadLevel()
{
	m_board.clearBoard();
	m_board.loadLevel(m_lvlNum);
}

void Controller::init()
{
	m_numOfLvl.setCharacterSize(CHAR_SIZE / 2);
	m_numOfLvl.setFillColor(sf::Color::Yellow);
	m_numOfLvl.setPosition({ 20,10 });

	m_backGround.setScale(WINDOW_DIMENSIONS.x / (m_backGround.getLocalBounds().width),
		                  WINDOW_DIMENSIONS.y / (m_backGround.getLocalBounds().height));

	m_key.setScale(0.7, 0.7);
	m_key.setPosition(120, 10);

	m_arrow.setScale(0.5, 0.5);
	m_arrow.setOrigin(m_arrow.getGlobalBounds().width / 2,
		              m_arrow.getGlobalBounds().height / 2);
}

void Controller::checkIflvlRestart(sf::RenderWindow& window, sf::Clock& clock)
{
	if (!(m_isRestart || GameManager::instance().isLvlLose()))
		return;
	ResourcesSounds::getInstance().play(Sounds::lvlLose);

	static auto youLose = ResourcesTxtrs::getInstance().getSprite(Type::youLose);
	printMessage(window, clock, youLose, 3.f);
	
	m_isRestart = false;
	loadLevel();
}
