#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <SFML/Graphics.hpp>
#include "../utils/Config.hpp"

class Camera {
public:
    Camera();

    void update(const sf::Vector2f& playerPosition, float deltaTime, bool isPaused, bool instant = false, const sf::FloatRect& zoneBounds = sf::FloatRect());
    void applyView(sf::RenderWindow& window);
    void resetToDefault();

private:
    sf::View view;
};

#endif // CAMERA_HPP