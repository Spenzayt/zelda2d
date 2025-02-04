#ifndef CHASER_HPP
#define CHASER_HPP

#include <SFML/Graphics.hpp>
#include "Entity.hpp"
#include "Enemy.hpp"
#include "Player.hpp"
#include <vector>
#include <string>

class Chaser : public Enemy {
private:
	sf::Sprite sprite;
	sf::Texture texture;
	const Player& player;
	float speed;
	sf::Vector2f position;
	int size;

	float visionRadius;
	bool isChasing;

	void initSprite();
	void initTexture();
public:
	Chaser(float s, sf::Vector2f p, int hp, int d, float size, const Player& playerRef);

	void update(float deltaTime, const std::vector<sf::Sprite>& bushes) override;
	void draw(sf::RenderWindow& window) override;
	sf::FloatRect getGlobalBounds() const override;
};



#endif // chaser_HPP