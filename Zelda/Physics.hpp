#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Physics {
public:
    static bool checkCollision(const sf::Sprite& entity, const std::vector<sf::RectangleShape>& walls);
};
