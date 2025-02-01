#include "MainMenu.hpp"

void MainMenu::initButtons()
{
    std::vector<std::string> buttonsMenu = { "Jouer", "Options", "Quitter" };
    for (size_t i = 0; i < buttonsMenu.size(); i++) {

        sf::Text button;
        button.setFont(font);
        button.setString(buttonsMenu[i]);
        button.setCharacterSize(50);
        button.setFillColor(sf::Color(168, 168, 168));

        sf::FloatRect boundsText = button.getLocalBounds();
        float x = (Config::WINDOW_WIDTH / 2.f) - (boundsText.width / 2.f) - boundsText.left;
        button.setPosition(x, 400 + static_cast<float>(i)* 80);
        buttons.push_back(button);
    }
}

MainMenu::MainMenu()
{
    initButtons();
}

int MainMenu::handleInput(sf::RenderWindow& window, const sf::Event& event) {
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        if (!isCooldownActive()) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            for (size_t i = 0; i < buttons.size(); i++) {
                if (buttons[i].getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                    resetCooldown();
                    return static_cast<int>(i);
                }
            }
        }
    }
    return -1;
}