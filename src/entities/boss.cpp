#include "Boss.hpp"
#include <iostream>

void Boss::initSprite()
{
	if (!texture.loadFromFile("assets/images/characters/boss.png")) {
		std::cerr << "Error: Unable to load the Boss texture from " << std::endl;
	}
}

void Boss::initTexture()
{
	sprite.setTexture(texture);
}

Boss::Boss(float s, sf::Vector2f p, int hp, int d, float size) : Enemy(s, p, hp, d), size(size), speed(s)
{
	initSprite();
	initTexture();
	position = p;

	sprite.setPosition(position);
	sprite.setScale(size *1.2f, size * 1.2f);
}

void Boss::update(float deltaTime, const std::vector<sf::Sprite>& bushes)
{

}

void Boss::draw(sf::RenderWindow& window)
{
	window.draw(sprite);
}

sf::FloatRect Boss::getGlobalBounds() const
{
	return sprite.getGlobalBounds();
}

int Boss::getDamage() const
{
	return damage;
}

