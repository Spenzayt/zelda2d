#pragma once
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

class InputHandler {
public:
    static sf::Vector2f getMovementDirection();
};
