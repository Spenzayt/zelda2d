#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <SFML/Graphics.hpp>
#include<vector>

class Entity {
public:

	virtual void update(float deltatime, const std::vector<sf::Sprite>& trees, const std::vector<sf::Sprite>& bushes) = 0;
	virtual void draw(sf::RenderWindow& window) = 0;

protected:
	int speed;
	int damage;
	int heal;

	sf::Vector2f position;
};

#endif // ENTITY_HPP