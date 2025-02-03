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

Archer::Archer(float s, sf::Vector2f p, int hp, int d, float size) : Enemy(s, p, hp, d), size(size), speed(s)
{
	initSprite();
	initTexture();

	position = p;
	sprite.setPosition(position);
	
}

void Archer::update(float deltaTime, const std::vector<sf::Sprite>& bushes)
{
	sprite.move(speed, 0.f);
}

void Archer::draw(sf::RenderWindow& window)
{
	window.draw(sprite);
}
