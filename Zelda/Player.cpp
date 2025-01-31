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

void Player::update(float deltatime) {
    handleInput(deltatime);
    player.setPosition(position);
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

sf::Vector2f Player::getPosition() const { 
    return player.getPosition();
}