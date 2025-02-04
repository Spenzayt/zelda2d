#ifndef  WIN_HPP
#define WIN_HPP

#include <SFML/Graphics.hpp>
#include <../src/ui/Renderer.hpp>

class Win : public Renderer {

protected:
	sf::Text text;
	sf::Font font;

	
public:
	void update() override;
	void draw(sf::RenderWindow& window) override;
};


#endif // ! WIN_HPP
