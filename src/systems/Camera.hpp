#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <SFML/Graphics.hpp>
#include "../entities/Player.hpp"
#include "../utils/Config.hpp"

class Camera {
public:
    Camera(float windowWidth, float windowHeight);

    void setRooms(const std::vector<sf::IntRect>& rooms);
    void update(const sf::Vector2f& playerPosition, float deltaTime, bool isInMenu = false);
    void applyView(sf::RenderWindow& window);

private:
    sf::View view;
    sf::Vector2f targetPosition;
    bool inRoom = false;
    bool canTransitioning = false;
    sf::IntRect currentRoom;
    std::vector<sf::IntRect> rooms;

    void checkRoomTransition(const sf::Vector2f& playerPosition);
    void updateForMenu();
};

#endif // CAMERA_HPP