#include "Menu.hpp"

void Menu::initFont()
{
    if (!font.loadFromFile("assets/font/test.otf")) {
    }
}

Menu::Menu() {
    initFont();
}



void Menu::handleMouseHover(const RenderWindow& window)
{
    Vector2i mousePos = Mouse::getPosition(window);
    for (auto& button : buttons) {
        if (button.getGlobalBounds().contains(static_cast<Vector2f>(mousePos))) {
            button.setFillColor(Color::White);
        }
        else {
            button.setFillColor(Color(168, 168, 168));
        }
    }
}

void Menu::render(RenderWindow& window)
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
