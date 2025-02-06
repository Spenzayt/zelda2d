#include "ProjectilesBoss.hpp"
#include <iostream>
#include <cmath>

void ProjectilesBoss::initSprite()
{
	if (!texture.loadFromFile("assets/images/projectiles/projectile_boss.png")) {
		std::cerr << "Error : Unable to load boss projo texture" << std::endl;
	}
}

void ProjectilesBoss::initTexture()
{
	sprite.setTexture(texture);

}

ProjectilesBoss::ProjectilesBoss(sf::Vector2f position, sf::Vector2f direction, float speed) : startPosition(position)
{
	initSprite();

	sprite.setPosition(position);
	sprite.setScale(1.5f, 1.5f);
	float magnitude = std::sqrt(direction.x * direction.x + direction.y * direction.y);
	velocity = (direction / magnitude) * speed;
}

void ProjectilesBoss::update(float deltaTime)
{
	sprite.move(velocity * deltaTime);
}

void ProjectilesBoss::draw(sf::RenderWindow& window)
{
	initTexture();
	window.draw(sprite);
}

sf::Vector2f ProjectilesBoss::getPosition() const
{
	return sprite.getPosition();
}

sf::FloatRect ProjectilesBoss::getGlobalBounds() const
{
	return sprite.getGlobalBounds();
}

sf::Vector2f ProjectilesBoss::getStartPosition() const
{
	return startPosition;
}

float ProjectilesBoss::getMaxDistance() const
{
	return maxDistance;
}
