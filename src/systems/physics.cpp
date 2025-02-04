#include "Physics.hpp"
#include <iostream>

bool Physics::checkCollision(const sf::Sprite& entity, const std::vector<sf::RectangleShape>& walls, sf::Vector2f& newPosition) {
    for (const auto& wall : walls) {
        if (entity.getGlobalBounds().intersects(wall.getGlobalBounds())) {
            newPosition = entity.getPosition();
            return true;
        }
    }
    return false;
}

void Physics::loadCollisionImage() {
    if (!collisionImage.loadFromFile("assets/images/map/collision_map.png")) {
        std::cerr << "Image Failed to Load : collision_map.png " << std::endl;
    }
}

void Physics::resizeCollisionImage(unsigned int newWidth, unsigned int newHeight) {
    resizedCollisionImage.create(newWidth, newHeight, sf::Color::Transparent);

    for (unsigned int y = 0; y < newHeight; ++y) {
        for (unsigned int x = 0; x < newWidth; ++x) {
            unsigned int originalX = static_cast<unsigned int>(x * (collisionImage.getSize().x / static_cast<float>(newWidth)));
            unsigned int originalY = static_cast<unsigned int>(y * (collisionImage.getSize().y / static_cast<float>(newHeight)));
            resizedCollisionImage.setPixel(x, y, collisionImage.getPixel(originalX, originalY));
        }
    }
}

bool Physics::isCollidingWithMap(const sf::FloatRect& hitbox) const {
    for (float x = hitbox.left; x < hitbox.left + hitbox.width; x++) {
        for (float y = hitbox.top; y < hitbox.top + hitbox.height; y++) {
            if (x < 0 || y < 0 || x >= resizedCollisionImage.getSize().x || y >= resizedCollisionImage.getSize().y) {
                return false;
            }

            sf::Color pixelColor = resizedCollisionImage.getPixel(static_cast<unsigned int>(x), static_cast<unsigned int>(y));
            if (pixelColor == sf::Color(255, 0, 0)) {
                return true;
            }
        }
    }
    return false;
}