#ifndef MAIN_MENU_HPP
#define MAIN_MENU_HPP

#include <SFML/Graphics.hpp>
#include "Menu.hpp"

class MainMenu : public Menu {
private:
    void initButtons() override;
public:
    MainMenu();

    int handleInput(sf::RenderWindow& window, const sf::Event& event) override;
};

#endif // MAIN_MENU_HPP