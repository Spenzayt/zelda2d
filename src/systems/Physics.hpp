#ifndef PHYSICS_HPP
#define PHYSICS_HPP

#include <SFML/Graphics.hpp>
#include <vector>

class Physics {
public:
    static bool checkCollision(const sf::Sprite& entity, const std::vector<sf::RectangleShape>& walls, sf::Vector2f& newPosition);
};

#endif // PHYSICS_HPP