#include <fstream>
#include "Menus/Play.h"
#include "Menus/Exit.h"
#include "Menus/Menu.h"
#include "ResourcesSounds.h"
#include "GameManager.h"


int WriteException2LogFile(const std::string& what)
{
    auto logfile = std::ofstream(LOG_FILE);

    logfile << what << std::endl;

    logfile.close();
    return EXIT_FAILURE;
}

int main() try
{
    auto window = sf::RenderWindow(sf::VideoMode(WINDOW_DIMENSIONS.x, WINDOW_DIMENSIONS.y),
        GAME, sf::Style::Titlebar | sf::Style::Close);
    //set cursor for mouse
    auto cursor = sf::Cursor();
    cursor.loadFromPixels(GameManager::instance().getCursorImg().getPixelsPtr(), 
                          GameManager::instance().getCursorImg().getSize(), sf::Vector2u({ 26,16 }));
    window.setMouseCursor(cursor);

    window.setFramerateLimit(60);
    window.setPosition({ 0, 0 });

    auto mainMenu = Menu(Menu_t::MENU);

    ResourcesSounds::getInstance().play(Sounds::Background);
    ResourcesSounds::getInstance().setLoop(Sounds::Background);
   
    mainMenu.add({ Menu_t::Play,  std::make_unique<Play>() });
    mainMenu.add({ Menu_t::Exit,  std::make_unique<Exit>() });

    mainMenu.run(window);
    return EXIT_SUCCESS;
}

//all the exceptions will be written into log file
catch (const std::exception& e)
{
    WriteException2LogFile(e.what());
}

catch (...)
{
    WriteException2LogFile("Unknown exception!\n");
}