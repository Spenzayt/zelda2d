#ifndef ARCHER_HPP
#define ARCHER_HPP

#include <SFML/Graphics.hpp>
#include "Entity.hpp"
#include "Enemy.hpp"
#include "Player.hpp"
#include "Arrow.hpp"
#include <vector>
#include <string>

class Archer : public Enemy {
private:
	sf::Sprite sprite;
	sf::Texture texture;
	float speed;
	sf::Vector2f position;
	int size;

	const Player& player;
	// flèches
	std::vector<Arrow> arrows;
	float shootCooldown = 2.0f;
	float timeSinceLastShot = 0.0f;
	float visionRadius;
	bool canShoot;


	// initialisation sprite
	void initSprite();
	void initTexture();
public:
	Archer(float s, sf::Vector2f p, int hp, int d, float size, const Player& refPlayer);

	void update(float deltaTime, const std::vector<sf::Sprite>& bushes) override;
	void shoot();

	void draw(sf::RenderWindow& window) override;
};



#endif // archer_HPP