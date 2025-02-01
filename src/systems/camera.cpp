#include "camera.hpp"
#include <iostream>

Camera::Camera(float windowWidth, float windowHeight) {
    view.setSize(windowWidth, windowHeight);
    view.setCenter(windowWidth / 2, windowHeight / 2);
    canTransitioning = true;
}

void Camera::setRooms(const std::vector<sf::IntRect>& rooms) {
    this->rooms = rooms;
}

void Camera::update(const sf::Vector2f& playerPosition, float deltaTime, bool isInMenu) {
    sf::Vector2f targetPosition;

    if (isInMenu) {
        updateForMenu();
        canTransitioning = false;
        return;
    }

    if (inRoom) {
        float x = currentRoom.left + currentRoom.width / 2;
        float y = currentRoom.top + currentRoom.height / 2;

        x = std::max(x, view.getSize().x / 2);
        y = std::max(y, view.getSize().y / 2);
        x = std::min(x, currentRoom.left + currentRoom.width - view.getSize().x / 2);
        y = std::min(y, currentRoom.top + currentRoom.height - view.getSize().y / 2);

        targetPosition = sf::Vector2f(x, y);
    }
    else {
        targetPosition = playerPosition;
    }

    if (canTransitioning) {
        sf::Vector2f currentCenter = view.getCenter();
        sf::Vector2f interpolatedPosition = currentCenter + (targetPosition - currentCenter) * deltaTime * 5.0f;
        view.setCenter(interpolatedPosition);
    }

    if (!canTransitioning) {
        view.setCenter(targetPosition);
    }

    if (!isInMenu) {
        canTransitioning = true;
    }

    checkRoomTransition(playerPosition);
}

void Camera::applyView(sf::RenderWindow& window) {
    window.setView(view);
}

void Camera::checkRoomTransition(const sf::Vector2f& playerPosition) {
    for (const auto& room : rooms) {
        if (room.contains(playerPosition.x, playerPosition.y)) {
            if (!inRoom || room != currentRoom) {
                currentRoom = room;
                inRoom = true;
            }
            return;
        }
    }
    inRoom = false;
}

void Camera::updateForMenu() {
    view.setCenter(Config::WINDOW_WIDTH/2, Config::WINDOW_HEIGHT / 2);
    inRoom = false;
}