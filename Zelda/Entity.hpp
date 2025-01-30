#pragma once
#include <SFML/Graphics.hpp>
#include<vector>

class Entity {


public:

	virtual void update(float deltatime) = 0;
	virtual void draw(sf::RenderWindow& window) = 0;


protected:

	int speed;
	int damage;
	int heal;

	sf::Vector2f position;

};