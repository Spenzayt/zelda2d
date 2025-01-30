#include "MainMenu.hpp"

void MainMenu::initButtons()
{
    std::vector<std::string> buttonsMenu = { "Jouer", "Options", "Quitter" };
    float windowWidth = 1920.0f;
    for (size_t i = 0; i < buttonsMenu.size(); i++) {

        Text button;
        button.setFont(font);
        button.setString(buttonsMenu[i]);
        button.setCharacterSize(50);
        button.setFillColor(Color(168, 168, 168));

        FloatRect boundsText = button.getLocalBounds();
        float x = (windowWidth / 2.f) - (boundsText.width / 2.f) - boundsText.left;
        button.setPosition(x, 400 + static_cast<float>(i)* 80);
        buttons.push_back(button);
    }
}

MainMenu::MainMenu()
{
    initButtons();
}

int MainMenu::handleInput(RenderWindow& window, const Event& event) {
    if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
        Vector2i mousePos = Mouse::getPosition(window);
        for (size_t i = 0; i < buttons.size(); i++) {
            if (buttons[i].getGlobalBounds().contains(static_cast<Vector2f>(mousePos))) {
                return static_cast<int>(i);
            }
        }
    }
    return -1;
}