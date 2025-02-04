#ifndef  RENDERER_HPP
#define RENDERER_HPP

#include <SFML/Graphics.hpp>
class Renderer {

protected:
	sf::Text text;
	sf::Font font;
public:
	virtual void update() = 0;
	virtual void draw(sf::RenderWindow& window) = 0;
};


#endif // ! RENDERER_HPP

