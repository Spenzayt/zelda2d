#include "Physics.hpp"

bool Physics::checkCollision(const sf::Sprite& entity, const std::vector<sf::RectangleShape>& walls) {
    for (const auto& wall : walls) {
        if (entity.getGlobalBounds().intersects(wall.getGlobalBounds())) {
            return true;  
        }
    }
    return false;  
}
