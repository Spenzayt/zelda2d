#include "Renderer.hpp"
#include <iostream>

void Renderer::initFont()
{
	if (!font.loadFromFile("assets/fonts/test.otf")) {
		std::cerr << "Error loading the font!" << std::endl;
	}
}

Renderer::Renderer()
{
	initFont();
}

void Renderer::draw(sf::RenderWindow& window)
{
	for (const auto& button : buttons) {
		window.draw(button);
	}
}

void Renderer::handleMouseHover(const sf::RenderWindow& window)
{
	sf::Vector2i mousePos = sf::Mouse::getPosition(window);

	for ( auto& button : buttons) {
		if (button.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
			button.setFillColor(sf::Color::White);
		}
		else {
			button.setFillColor(sf::Color(168, 168, 168));
		}
	}
}

bool Renderer::isCooldownActive()
{
	return cooldownMouseClock.getElapsedTime().asSeconds();
}

void Renderer::resetCooldown()
{
	cooldownMouseClock.restart();
}
