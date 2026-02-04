#ifndef ARCHER_HPP
#define ARCHER_HPP

#include <SFML/Graphics.hpp>
#include "Player.hpp"
#include "Enemy.hpp"
#include "Arrow.hpp"
#include "../systems/SoundManager.hpp"
#include <vector>
#include <string>

class Player;

class Archer : public Enemy {
private:
	sf::Sprite sprite;
	sf::Texture texture;
	float speed;
	float distanceTraveled = 0.f;
	sf::Vector2f position;
	float size;
	Player& player;
	SoundManager& soundManager;

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
	Archer(float s, sf::Vector2f p, int hp, int d, float size, Player& refPlayer, SoundManager& sm);

	void update(float deltaTime, const std::vector<sf::Sprite>& bushes) override;
	void shoot();

	int getDamage() const override;
	sf::FloatRect getGlobalBounds() const override;

	void draw(sf::RenderWindow& window) override;
};



#endif // archer_HPP