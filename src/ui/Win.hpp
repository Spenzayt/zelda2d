#ifndef  WIN_HPP
#define WIN_HPP

#include <SFML/Graphics.hpp>
#include "Renderer.hpp"

class Win : public Renderer {

protected:
	sf::Text text;
	sf::Font font;

	void initWin();
	void initButtons() override;
public:
	Win();
	
	void draw(sf::RenderWindow& window) override;

	int handleInput(sf::RenderWindow& window, const sf::Event& event) override;
};

#endif // ! WIN_HPP
