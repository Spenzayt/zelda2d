#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player.hpp"
#include "InputHandler.hpp"
#include "Physics.hpp"

Player::Player(sf::Vector2f spawnposition, float size, const std::string& texturePath) : hasKey(false)
{
    position = spawnposition;
    previousPosition = position;

    
    damage = 10;
    heal = 100;
    speed = 400;

    
    if (!texture.loadFromFile(texturePath)) {
        std::cerr << "Erreur lors du chargement de la texture !" << std::endl;
    }

    player.setTexture(texture);
    player.setScale(size / texture.getSize().x, size / texture.getSize().y);  
    player.setPosition(position);
}
void Player::update(float deltatime, const std::vector<sf::Sprite>& trees, const std::vector<sf::Sprite>& bushes) {
    previousPosition = position;
    handleInput(deltatime);
    player.setPosition(position);

    checkCollisionWithMap(trees, bushes);
}

void Player::handleInput(float deltatime) {
    previousPosition = position;

    sf::Vector2f movement = InputHandler::getMovementDirection();
    position.x += movement.x * speed * deltatime;
    position.y += movement.y * speed * deltatime;

}
void Player::increaseSpeed(float amount) {
    speed += amount;
}

void Player::collectKey() {
    hasKey = true;
    std::cout << "Player has the key!" << std::endl;
}

void Player::draw(sf::RenderWindow& window) {
    window.draw(player);
}


void Player::checkCollisionWithWalls(const std::vector<sf::RectangleShape>& walls) {
    if (Physics::checkCollision(player, walls)) {
        position = previousPosition;  
        player.setPosition(position);
    }
}
void Player::checkCollisionWithMap(const std::vector<sf::Sprite>& trees, const std::vector<sf::Sprite>& bushes) {
    for (const auto& tree : trees) {
        if (player.getGlobalBounds().intersects(tree.getGlobalBounds())) {
            position = previousPosition;
            player.setPosition(position);
            return;
        }
    }

    for (const auto& bush : bushes) {
        if (player.getGlobalBounds().intersects(bush.getGlobalBounds())) {
            position = previousPosition;
            player.setPosition(position);
            return;
        }
    }
}


sf::Vector2f Player::getPosition() const { 
    return player.getPosition();
}
