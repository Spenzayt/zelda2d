#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <SFML/Graphics.hpp>
#include "Entity.hpp"
#include <string>
#include <vector>


class Enemy : public Entity {
protected:
	float speed;
	int heal;
	int damage;

	sf::Vector2f position;
public:
	Enemy(float s, sf::Vector2f p, int hp, int d);

	void update(float deltatime, const std::vector<sf::Sprite>& bushes) override = 0;
	void draw(sf::RenderWindow& window) override = 0;

	virtual sf::FloatRect getGlobalBounds() const = 0;

};

#endif // ENEMY_HPP