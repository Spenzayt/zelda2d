#ifndef  RENDERER_HPP
#define RENDERER_HPP

#include <SFML/Graphics.hpp>
#include "../utils/Config.hpp"
class Renderer {

protected:
	sf::Text text;
	sf::Font font;
	std::vector<sf::Text> buttons;

	sf::Clock cooldownMouseClock;
	const sf::Time cooldownMouse;

	virtual void initFont();
	virtual void initButtons() = 0;
public:
	Renderer();
	virtual void draw(sf::RenderWindow& window);

	virtual int handleInput(sf::RenderWindow& window, const sf::Event& event) = 0;
	
	virtual void handleMouseHover(const sf::RenderWindow& window);

	bool isCooldownActive();
	void resetCooldown();
};


#endif // ! RENDERER_HPP

