#ifndef  ARROW_HPP
#define ARROW_HPP

#include <SFML/Graphics.hpp>


class Arrow {
private:
	sf::Sprite sprite;
	sf::Texture texture;
	sf::Vector2f velocity;
	sf::Vector2f startPosition;
	float maxDistance = 1000.f;
	float speed;

	void initSprite();
	void initTexture();
public:
	Arrow(sf::Vector2f position, sf::Vector2f direction, float speed);

	void update(float deltaTime);
	void draw(sf::RenderWindow& window);

	sf::Vector2f getPosition() const;
	sf::FloatRect getGlobalBounds() const;
	sf::Vector2f getStartPosition() const;
	float getMaxDistance() const;
};

#endif // ! ARROW_HPP

