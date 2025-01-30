#include "Menu.hpp"

Menu::Menu(std::shared_ptr<Font> sharedFont) : font(sharedFont) {}

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