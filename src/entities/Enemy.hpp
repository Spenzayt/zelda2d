#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <SFML/Graphics.hpp>
#include "Entity.hpp"
#include <string>
#include <vector>


class Enemy : public Entity {
protected:
	float speed;
	int heal = 30;
	int damage;

	sf::Vector2f position;
public:
	Enemy(float s, sf::Vector2f p, int hp, int d);

	void update(float deltatime, const std::vector<sf::Sprite>& bushes) override = 0;
	void draw(sf::RenderWindow& window) override = 0;

	virtual int getDamage() const = 0;
	virtual sf::FloatRect getGlobalBounds() const = 0;

	void takeDamage(int dmg);
	bool isAlive() const;
	bool isDead() const;
	sf::Vector2f getPosition() const { return position; }


};

#endif // ENEMY_HPP