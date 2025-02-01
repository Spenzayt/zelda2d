#include "camera.hpp"

Camera::Camera() {
    view.setSize(Config::WINDOW_WIDTH, Config::WINDOW_HEIGHT);
    view.setCenter(Config::WINDOW_WIDTH / 2, Config::WINDOW_HEIGHT / 2);
}

void Camera::update(const sf::Vector2f& playerPosition, float deltaTime, bool isPaused, bool instant, const sf::FloatRect& zoneBounds) {
    if (!isPaused) {
        sf::Vector2f targetPosition = playerPosition;

        if (instant) {
            view.setCenter(targetPosition);
        }
        else {
            sf::Vector2f currentCenter = view.getCenter();
            sf::Vector2f newCenter = currentCenter + (targetPosition - currentCenter) * 0.1f;

            newCenter.x = std::max(zoneBounds.left + Config::WINDOW_WIDTH / 2, std::min(newCenter.x, zoneBounds.left + zoneBounds.width - Config::WINDOW_WIDTH / 2));
            newCenter.y = std::max(zoneBounds.top + Config::WINDOW_HEIGHT / 2, std::min(newCenter.y, zoneBounds.top + zoneBounds.height - Config::WINDOW_HEIGHT / 2));

            view.setCenter(newCenter);
        }
    }
}

void Camera::applyView(sf::RenderWindow& window) {
    window.setView(view);
}

void Camera::resetToDefault() {
    view.setCenter(Config::WINDOW_WIDTH / 2, Config::WINDOW_HEIGHT / 2);
}