#ifndef PHYSICS_HPP
#define PHYSICS_HPP

#include <SFML/Graphics.hpp>
#include <vector>

class Physics {
private:
    sf::Image collisionImage;
    sf::Image resizedCollisionImage;

public:
    static bool checkCollision(const sf::Sprite& entity, const std::vector<sf::RectangleShape>& walls, sf::Vector2f& newPosition);
    void loadCollisionImage();
    void resizeCollisionImage(unsigned int newWidth, unsigned int newHeight);
    bool isCollidingWithMap(const sf::FloatRect& hitbox) const;
};

#endif // PHYSICS_HPP