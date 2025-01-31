#include "Physics.hpp"

bool Physics::checkCollision(const sf::Sprite& entity, const std::vector<sf::RectangleShape>& walls, sf::Vector2f& newPosition) {
    for (const auto& wall : walls) {
        if (entity.getGlobalBounds().intersects(wall.getGlobalBounds())) {
            newPosition = entity.getPosition();
            return true;
        }
    }
    return false;
}