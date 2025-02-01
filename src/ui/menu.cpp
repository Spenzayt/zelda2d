#include "Menu.hpp"
#include <iostream>

void Menu::initFont()
{
    if (!font.loadFromFile("assets/fonts/test.otf")) {
        std::cout << "Error loading the font!" << std::endl;
    }
}

Menu::Menu() {
    initFont();
}

void Menu::handleMouseHover(const sf::RenderWindow& window)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    for (auto& button : buttons) {
        if (button.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
            button.setFillColor(sf::Color::White);
        }
        else {
            button.setFillColor(sf::Color(168, 168, 168));
        }
    }
}

void Menu::render(sf::RenderWindow& window)
{
    for (const auto& button : buttons) {
        window.draw(button);
    }
}

bool Menu::isCooldownActive()
{
    return cooldownMouseClock.getElapsedTime() < cooldownMouse;
}

void Menu::resetCooldown()
{
    cooldownMouseClock.restart();
}