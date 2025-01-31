#ifndef INPUT_HANDLER_HPP
#define INPUT_HANDLER_HPP

#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

class InputHandler {
public:
    static sf::Vector2f getMovementDirection();
};

#endif // INPUT_HANDLER_HPP