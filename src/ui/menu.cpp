#include "Menu.hpp"
#include <iostream>

void Menu::initFont()
{
    if (!font.loadFromFile("assets/fonts/test.otf")) {
        std::cout << "Error loading the font!" << std::endl;
    }
}

int Menu::initMenuTexture()
{
    if (!texture.loadFromFile("assets/images/menu/wallpapersword.jpg"));
    return -1;
}

void Menu::initSpriteMenu()
{
    menu.setTexture(texture);
    menu.setPosition(0, 0);
}

Menu::Menu() {
    initFont();
    initMenuTexture();
    initSpriteMenu();
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

    for (size_t i = 0; i < buttons.size(); i++) {
        bool isHoveredText = buttons[i].getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos));
        bool isHoveredShape = i < keyShapes.size() && keyShapes[i].getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos));

        if (isHoveredText || isHoveredShape) {
            if (i < keyShapes.size()) keyShapes[i].setFillColor(sf::Color::Black);
            buttons[i].setFillColor(sf::Color::White);
        }
        else {
            if (i < keyShapes.size()) keyShapes[i].setFillColor(sf::Color(0, 0, 0, 150));
            buttons[i].setFillColor(sf::Color(168, 168, 168));
        }   
    }

    if (returnText.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
        returnButton.setFillColor(sf::Color::Black);
        returnText.setFillColor(sf::Color::White);
    }
    else {
        returnButton.setFillColor(sf::Color(0, 0, 0, 150));
        returnText.setFillColor(sf::Color(168, 168, 168));
    }
}

void Menu::render(sf::RenderWindow& window)
{
    window.draw(menu);
    for (const auto& keys : keyShapes) {
        window.draw(keys);
    }
    for (const auto& keys : keysRect) {
        window.draw(keys);
    }
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