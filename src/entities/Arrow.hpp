#ifndef  ARROW_HPP
#define ARROW_HPP

#include <SFML/Graphics.hpp>


class Arrow {
private:
	sf::Sprite sprite;
	sf::Texture texture;
	sf::Vector2f velocity;
	float speed;

	void initSprite();
	void initTexture();
public:
	Arrow(sf::Vector2f position, sf::Vector2f direction, float speed);

	void update(float deltaTime);
	void draw(sf::RenderWindow& window);
	sf::FloatRect getGlobalBounds() const;
};

#endif // ! ARROW_HPP

