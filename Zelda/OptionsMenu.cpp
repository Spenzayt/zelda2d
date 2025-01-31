#include "OptionsMenu.hpp"

void OptionsMenu::initButtons()
{
	vector<string> optionsButtons = { "Volume : 100%", "Changer touches", "Retour" };
	float windowWidth = 1920.f;
	for (size_t i = 0; i < optionsButtons.size(); i++) {
		Text button;
		button.setFont(font);
		button.setString(optionsButtons[i]);
		button.setCharacterSize(50);
		button.setFillColor(Color(168, 168, 168));

		FloatRect textBounds = button.getLocalBounds();
		float x = (windowWidth / 2.f) - (textBounds.width / 2.f) - textBounds.left;
		button.setPosition(x, 400 + static_cast<float>(i) * 80);
		buttons.push_back(button);
	}
}

void OptionsMenu::updateTextVolume()
{
	buttons[0].setString("Volume :" + to_string((int)volumeLevel) + "%");
}

OptionsMenu::OptionsMenu() : volumeLevel(100)
{
	initButtons();
}

int OptionsMenu::handleInput(RenderWindow& window, const Event& event)
{
	if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
		if (!isCooldownActive()) {
			Vector2i mousePos = Mouse::getPosition(window);
			for (size_t i = 0; i < buttons.size(); i++) {
				if (buttons[i].getGlobalBounds().contains(static_cast<Vector2f>(mousePos))) {
					resetCooldown();
					if (i == 0) {
						volumeLevel = (volumeLevel == 100) ? 50 : 100;
						updateTextVolume();
					}
					else if (i == 2) {
						return 2;
					}
					
				}
			}
		}
	}
	return -1;
}


