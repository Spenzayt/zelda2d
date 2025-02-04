#include "Archer.hpp"
#include <cmath>
#include <iostream>

void Archer::initSprite()
{
	if (!texture.loadFromFile("assets/images/characters/archer.png")) {
		std::cerr << "Error: Unable to load the Blob texture from " << std::endl;
	}
}

void Archer::initTexture()
{
	sprite.setTexture(texture);
	sprite.setScale(0.6f, 0.6f);
}

Archer::Archer(float s, sf::Vector2f p, int hp, int d, float size, const Player& refPlayer) : Enemy(s, p, hp, d), size(size), speed(s), player(refPlayer),
visionRadius(600.f), canShoot(false)
{
	initSprite();
	initTexture();

	position = p;
	sprite.setPosition(position);
	
}

void Archer::update(float deltaTime, const std::vector<sf::Sprite>& bushes)
{
	sf::Vector2f playerPos = player.getPosition();
	sf::Vector2f arrowStartPos = sprite.getPosition();
	sf::Vector2f direction = playerPos - arrowStartPos;

	float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

	if (distance <= visionRadius) {
		canShoot = true;
	}
	else {
		canShoot = false;
	}
	if (canShoot) {
		timeSinceLastShot += deltaTime;
		if (timeSinceLastShot >= shootCooldown) {
			shoot();
			timeSinceLastShot = 0.f;
		}
	}
  	
	for (auto& arrow : arrows) {
		arrow.update(deltaTime);
	}
}

void Archer::shoot()
{
	sf::Vector2f playerPos = player.getPosition();
	sf::Vector2f arrowStartPos = sprite.getPosition();
	sf::Vector2f direction = playerPos - arrowStartPos;

	float magnitude = std::sqrt(direction.x * direction.x + direction.y * direction.y);

	if (magnitude != 0) {
		direction /= magnitude;
	}
	arrows.emplace_back(arrowStartPos, direction, 300.f);
	
}

int Archer::getDamage() const
{
	return damage;
}

sf::FloatRect Archer::getGlobalBounds() const
{
	return sprite.getGlobalBounds();
}

void Archer::draw(sf::RenderWindow& window)
{
	window.draw(sprite);
	for (auto& arrow : arrows) {
		arrow.draw(window);
	}
}
