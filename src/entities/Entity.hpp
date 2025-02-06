#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <SFML/Graphics.hpp>
#include<vector>

class Entity {
public:
	virtual void update(float deltaTime, const std::vector<sf::Sprite>& bushes) = 0;
	virtual void draw(sf::RenderWindow& window) = 0;

protected:
	int speed;
	int damage;
	float heal;

	sf::Vector2f position;
};

#endif // ENTITY_HPP