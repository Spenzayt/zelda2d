#include "Chaser.hpp"
#include <cmath>
#include <iostream>

void Chaser::initSprite()
{
	if (!texture.loadFromFile("assets/images/characters/blob.png")) {
		std::cerr << "Error: Unable to load the Blob texture from " << std::endl;
	}
}

void Chaser::initTexture()
{
	sprite.setTexture(texture);
}

Chaser::Chaser(float s, sf::Vector2f p, int hp, int d, float size, const Player& playerRef) : Enemy(s, p, hp, d), size(size), position(p), speed(s), 
player(playerRef), visionRadius(500), isChasing(false)
{
	initSprite();
	initTexture();

	sprite.setPosition(position);
	sprite.setScale(0.7, 0.7);
}

void Chaser::update(float deltaTime, const std::vector<sf::Sprite>& bushes)
{
	sf::Vector2f playerPos = player.getPosition();
	sf::Vector2f enemyPos = sprite.getPosition();
	sf::Vector2f direction = playerPos - enemyPos;

	float distance = sqrt(direction.x * direction.x + direction.y * direction.y);
	if (distance <= visionRadius) {
		isChasing = true;
	}
	else {
		isChasing = false;
	}
	if (isChasing) {
		if (distance != 0) {
			direction /= distance;
		}
		sf::Vector2f movement = direction * speed;
		sprite.move(movement);
	}
}

void Chaser::draw(sf::RenderWindow& window)
{
	window.draw(sprite);
}

int Chaser::getDamage() const
{
	return damage;
}

sf::FloatRect Chaser::getGlobalBounds() const
{
	return sprite.getGlobalBounds();
}
