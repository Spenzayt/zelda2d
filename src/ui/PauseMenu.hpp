#ifndef PAUSE_MENU_HPP
#define PAUSE_MENU_HPP

#include <SFML/Graphics.hpp>
#include "Menu.hpp"

class PauseMenu : public Menu
{
private:
	void initButtons() override;
public:
	PauseMenu();

	int handleInput(sf::RenderWindow& window, const sf::Event& event) override;
};

#endif // PAUSE_MENU_HPP