#include "Menus/Command.h"
#include "GameManager.h"
#include "ResourcesSounds.h"


Command::Command(Type type, const sf::Vector2f& position, const std::string& string,
    Fonts font, const sf::Vector2f& size) :
    m_menuButton(type, font, position, size, string)
{}
//----------------------------------------------------------------------------
void Command::draw(sf::RenderWindow& window)const
{
    m_menuButton.draw(window);
}

bool Command::isButtonPressed(const sf::Vector2f& mousePos)
{
    if (m_menuButton.clicked(mousePos)) {
        ResourcesSounds::getInstance().play(Sounds::Click);
        return true;
    }
    return false;
}