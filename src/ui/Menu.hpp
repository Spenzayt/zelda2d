#ifndef MENU_HPP
#define MENU_HPP

#include <SFML/Graphics.hpp>
#include "../utils/Config.hpp"

class Menu {
protected:
    sf::Font font;  
    std::vector<sf::Text> buttons;
    std::vector<sf::RectangleShape> keyShapes;
    std::vector<sf::RectangleShape> keysRect;

    sf::RectangleShape returnButton;
    sf::Text returnText;

    // temps entre chaque clic 
    sf::Clock cooldownMouseClock;
    const sf::Time cooldownMouse;


    // fond du menu
    sf::Texture texture;
    sf::Sprite menu;
    virtual void initButtons() = 0;
    void initFont();
    int initMenuTexture();
    void initSpriteMenu();

public:
    Menu();

    virtual int handleInput(sf::RenderWindow& window, const sf::Event& event) = 0;
    virtual void handleMouseHover(const sf::RenderWindow& window);

    virtual void render(sf::RenderWindow& window);

    bool isCooldownActive();
    void resetCooldown();
};

#endif // MENU_HPP