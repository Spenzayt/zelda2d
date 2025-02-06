#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <SFML/Graphics.hpp>
#include "../utils/Config.hpp"

class Camera {
public:
    Camera();

    void update(const sf::Vector2f& playerPosition, float deltaTime, bool isPaused, bool instant = false, const sf::FloatRect& zoneBounds = sf::FloatRect(), float zoom = 1.2f);
    void applyView(sf::RenderWindow& window);
    void resetToDefault();

    void setZoom(float zoomLevel);

private:
    sf::View view;
    float zoomLevel;
};

#endif // CAMERA_HPP