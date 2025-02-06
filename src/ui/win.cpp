#include "Win.hpp"
#include <iostream>

void Win::initWin()
{
	text.setFont(font);
	text.setString("VICTORY");
	text.setCharacterSize(120);
	text.setFillColor(sf::Color::Yellow);

	sf::FloatRect winBounds = text.getLocalBounds();
	float x = (Config::WINDOW_WIDTH / 2.f) - (winBounds.width / 2.f) - winBounds.left;
	text.setPosition(x, 300);

}

void Win::initFont(){
	if (!font.loadFromFile("assets/fonts/test.otf")) {
		std::cerr << "Error loading the font!" << std::endl;
	}
}

void Win::initButtons()
{
	std::vector<std::string> buttonsGameOver = { "Recommencer", "Quitter" };

	for (size_t i = 0; i < buttonsGameOver.size(); i++) {
		sf::Text button;
		button.setFont(font);
		button.setString(buttonsGameOver[i]);
		button.setCharacterSize(50);
		button.setFillColor(sf::Color(168, 168, 168));

		sf::FloatRect boundsText = button.getLocalBounds();
		float x = (Config::WINDOW_WIDTH / 2.f) - (boundsText.width / 2.f) - boundsText.left;
		button.setPosition(x, 500 + static_cast<float>(i) * 80);
		buttons.push_back(button);
	}
}

Win::Win()
{
	initFont();
	initWin();
	initButtons();
}

void Win::draw(sf::RenderWindow& window)
{
	window.draw(text);
	Renderer::draw(window);
}

int Win::handleInput(sf::RenderWindow& window, const sf::Event& event)
{
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
