#ifndef  GAMEOVER_HPP
#define GAMEOVER_HPP

#include <SFML/Graphics.hpp>
#include "Renderer.hpp"

class GameOver : public Renderer {

protected:
	sf::Text text;
	sf::Font font;
	
	void initFont() override;
	void initGameOver();
	void initButtons() override;
public:
	GameOver();

	void draw(sf::RenderWindow& window);

	int handleInput(sf::RenderWindow& window, const sf::Event& event) override;
};


#endif // ! GAMEOVER_HPP
