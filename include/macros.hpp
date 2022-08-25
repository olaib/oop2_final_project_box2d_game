#pragma once
#include "SFML/Graphics.hpp"

const auto NUM_OF_LEVELS = 6;
const auto LEVEL = "Level: ";
const auto NO_COMMAND_SELECTED = -1;
const auto RESET = 0;
const auto NO_PLAYERS = 0;
const auto PINKY_COLOR = sf::Color(191, 104, 173);
const auto EmptyTile = ' ';
const auto FIRST_LEVEL = 1;

const auto INSTRUCTIONS = "Move: WAD or arrow keys\nSwitch: down arrow\nTo restart level or back: by pause menu";

const auto GAME = "The Brothers";
const auto LOG_FILE = "resources/log.txt";

const auto SFML_SCALE = 0.0025f;
const auto EXIT = false;
const auto RUNNING = true;

const auto BOARD_WIDTH = 24;
const auto BOARD_HEIGHT = 16;

const auto TIME_STEP = 1.0f / 60.0f;
const auto WINDOW_DIMENSIONS = sf::Vector2i(1400,900);

//==============================================================
const auto SMALL_BUTTON_DIMENSIONS = sf::Vector2f(100, 100);
const auto LEVELS_PADDING = WINDOW_DIMENSIONS.x - SMALL_BUTTON_DIMENSIONS.x * NUM_OF_LEVELS;

const auto CELL_DIMENSIONS = sf::Vector2f(float(WINDOW_DIMENSIONS.x) / BOARD_WIDTH,
										  float(WINDOW_DIMENSIONS.y) / BOARD_HEIGHT);

const auto MENU_DIMENSIONS = sf::Vector2f(300, 100);
const auto MENU_BUTTON_DIMENSIONS = sf::Vector2f(300, 100);
const auto LEVEL_MENU_DIMENSIONS = sf::Vector2f(float(WINDOW_DIMENSIONS.x), 
												float(WINDOW_DIMENSIONS.y / 2));

const auto PAUSE_MENU_BUTTON_PADDING = (WINDOW_DIMENSIONS.x - SMALL_BUTTON_DIMENSIONS.x * 3) / 8;

//============================= SIZES ============================
const auto ANIMATION_SPEED = 0.3f;
const auto BOX2D_SCALE = 100.f;
const auto RADIAN_TO_DEGREE = (180 / 3.14);
const float EIGHTH_RATIO = 0.125f,
            QUARTER_RATIO = 0.25f,
            HALF_RATIO = 0.5f,
            ONE_AND_HALF_RATIO = 1.5f,
            STANDARD_RATIO = 1.f,
			DOUBLE_RATIO = 1.9f;

const auto CHAR_SIZE = 50;
//===========================enums================================

enum class Type : size_t
{
	Background,
	Background2,
	Cursor,
	Tile,
	Box,
	Thorn,
	Big,
	Small,
	Tall,
	BlockedTile,
	Key,
	Gate,
	arrow,
	Help,
	infoScreen,
	PlayBtn,
	menuButton,
	HomeBtn,
	restartBtn,
	resumeBtn,
	pauseBtn,
	levelsButton,
	musicOn,
	musicOff,
	GameOver,
	youLose,
	title
};

enum class Fonts : size_t
{
	Font1,
	Font2,
	Font3,
	Font4,
	Font5
};

enum class Menu_t :size_t
{
	Play,
	Options,
	Exit,
	MENU,
	level,
	homeMenu,
	Restart,
	Resume,
	Levels,
	pauseMenu,
	levelsMenu
};

enum class GameStatus :size_t
{
	MENU,
	Playing,
	NewLevel,
	RestartLevel,
	PauseMenu,
	EndGame
};

enum class Sounds : size_t
{
	Click,
	Background,
	Jump,
	EndLevels,
	win,
	lvlLose,
	key,
	endGame,
	gameOver
};