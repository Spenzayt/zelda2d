#ifndef  GAMEOVER_HPP
#define GAMEOVER_HPP

#include <SFML/Graphics.hpp>
#include <../src/ui/Renderer.hpp>

class GameOver : public Renderer {

protected:
	sf::Text text;
	sf::Font font;
public:
	void update() override;
	void draw(sf::RenderWindow& window) override;
};


#endif // ! GAMEOVER_HPP
