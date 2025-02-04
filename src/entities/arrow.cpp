#include "Arrow.hpp"
#include <iostream>
#include <cmath>

void Arrow::initSprite()
{
	if (!texture.loadFromFile("assets/images/projectiles/arrowtest.png")) {
		std::cerr << "Error : Unable to load arrow texture" << std::endl;
	}
}

void Arrow::initTexture(){
	sprite.setTexture(texture);
}

Arrow::Arrow(sf::Vector2f position, sf::Vector2f direction, float speed) {
	initSprite();
	initTexture();

	sprite.setPosition(position);
	sprite.setScale(1.5f, 1.5f);
	float magnitude = std::sqrt(direction.x * direction.x + direction.y * direction.y);
	velocity = (direction / magnitude) * speed;
}

void Arrow::update(float deltaTime) {
	sprite.move(velocity * deltaTime);
}

void Arrow::draw(sf::RenderWindow& window)
{
	window.draw(sprite);
}

sf::FloatRect Arrow::getGlobalBounds() const
{
	return sprite.getGlobalBounds();
}
