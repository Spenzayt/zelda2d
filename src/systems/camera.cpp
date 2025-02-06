#include "camera.hpp"
#include <iostream>

Camera::Camera() : zoomLevel(1.0f) {
    view.setSize(Config::WINDOW_WIDTH, Config::WINDOW_HEIGHT);
    view.setCenter(Config::WINDOW_WIDTH / 2, Config::WINDOW_HEIGHT / 2);
}

void Camera::setZoom(float zoomLevel) {
    this->zoomLevel = zoomLevel;
    view.setSize(Config::WINDOW_WIDTH / zoomLevel, Config::WINDOW_HEIGHT / zoomLevel);
}

void Camera::update(const sf::Vector2f& playerPosition, float deltaTime, bool isPaused, bool instant, const sf::FloatRect& zoneBounds, float zoom) {
    if (!isPaused) {
        sf::Vector2f targetPosition = playerPosition;

        if (instant) {
            view.setCenter(targetPosition);
            setZoom(zoom);
            std::cout << "error : Player is outside the map" << std::endl;
        }

       else {
            sf::Vector2f currentCenter = view.getCenter();
            sf::Vector2f newCenter = currentCenter + (targetPosition - currentCenter) * 0.1f;

            setZoom(zoom);

            float adjustedWidth = std::min(zoneBounds.width, static_cast<float>(Config::WINDOW_WIDTH) / zoomLevel);
            float adjustedHeight = std::min(zoneBounds.height, static_cast<float>(Config::WINDOW_HEIGHT) / zoomLevel);

            float centeredX = std::max(zoneBounds.left + adjustedWidth / 2, std::min(newCenter.x, zoneBounds.left + zoneBounds.width - adjustedWidth / 2));
            float centeredY = std::max(zoneBounds.top + adjustedHeight / 2, std::min(newCenter.y, zoneBounds.top + zoneBounds.height - adjustedHeight / 2));

            if (zoneBounds.width <= Config::WINDOW_WIDTH / zoomLevel) {
                centeredX = zoneBounds.left + zoneBounds.width / 2;
            }
            if (zoneBounds.height <= Config::WINDOW_HEIGHT / zoomLevel) {
                centeredY = zoneBounds.top + zoneBounds.height / 2;
            }

            newCenter.x = centeredX;
            newCenter.y = centeredY;

            view.setCenter(newCenter);
        }
    }
}

void Camera::applyView(sf::RenderWindow& window) {
    window.setView(view);
}

void Camera::resetToDefault() {
    view.setCenter(Config::WINDOW_WIDTH / 2, Config::WINDOW_HEIGHT / 2);
    setZoom(1.0f);
}