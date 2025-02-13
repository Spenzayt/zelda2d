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

Arrow::Arrow(sf::Vector2f position, sf::Vector2f direction, float speed) : startPosition(position) {
	initSprite();
	
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
	initTexture();
	window.draw(sprite);
}

sf::Vector2f Arrow::getPosition() const
{
	return sprite.getPosition();
}

sf::FloatRect Arrow::getGlobalBounds() const
{
	return sprite.getGlobalBounds();
}

sf::Vector2f Arrow::getStartPosition() const
{
	return startPosition;
}

float Arrow::getMaxDistance() const
{
	return maxDistance;
}
