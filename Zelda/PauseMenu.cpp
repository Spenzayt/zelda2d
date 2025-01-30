#include "PauseMenu.hpp"

void PauseMenu::initButtons()
{
    std::vector<std::string> buttonsPauseMenu = { "Reprendre", "Options", "Retour au menu" };
    float windowWidth = 1920.0f;
    for (size_t i = 0; i < buttonsPauseMenu.size(); i++) {

        Text button;
        button.setFont(font);
        button.setString(buttonsPauseMenu[i]);
        button.setCharacterSize(50);
        button.setFillColor(Color(168, 168, 168));

        FloatRect boundsText = button.getLocalBounds();
        float x = (windowWidth / 2.f) - (boundsText.width / 2.f) - boundsText.left;
        button.setPosition(x, 400 + static_cast<float>(i) * 80);
        buttons.push_back(button);
    }
}

PauseMenu::PauseMenu()
{
    initButtons();
}

int PauseMenu::handleInput(RenderWindow& window, const Event& event)
{
    if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left) {
        if (!isCooldownActive()) {
            Vector2i mousePos = Mouse::getPosition(window);
            for (size_t i = 0; i < buttons.size(); i++) {
                if (buttons[i].getGlobalBounds().contains(static_cast<Vector2f>(mousePos))) {
                    resetCooldown();
                    return static_cast<int>(i);
                }
            }
        }
    }
    return -1;
}
