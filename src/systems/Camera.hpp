#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <SFML/Graphics.hpp>
#include "../entities/Player.hpp"

class Camera {
public:
    Camera(float windowWidth, float windowHeight);

    void setRooms(const std::vector<sf::IntRect>& rooms);
    void update(const sf::Vector2f& playerPosition, float deltaTime);
    void applyView(sf::RenderWindow& window);

private:
    sf::View view;
    sf::Vector2f targetPosition;
    bool inRoom = false;
    sf::IntRect currentRoom;
    std::vector<sf::IntRect> rooms;

    void checkRoomTransition(const sf::Vector2f& playerPosition);
};

#endif // CAMERA_HPP