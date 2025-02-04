#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player.hpp"
#include "../core/InputHandler.hpp"
#include "../systems/Physics.hpp"

Player::Player(sf::Vector2f spawnposition, float size, const std::string& texturePath, float hp) : hasKey(false)
{
    position = spawnposition;
    previousPosition = position;

    maxHp = 5;
    heal = hp;

   // damage = 10;
    speed = 400;

    if (!texture.loadFromFile(texturePath)) {
        std::cerr << "Error loading texture from: " << texturePath << std::endl;
    }

    player.setTexture(texture);
    player.setScale(size / static_cast<float>(texture.getSize().x), size / static_cast<float>(texture.getSize().y));
    player.setPosition(position);
}

void Player::update(float deltatime, const std::vector<sf::Sprite>& bushes) {
    previousPosition = position;
    handleInput(deltatime);
    player.setPosition(position);

    checkCollisionWithMap(bushes);
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

    static sf::Font font;
    if (font.getInfo().family.empty()) {
        if (!font.loadFromFile("assets/fonts/arial.ttf")) {
            std::cerr << "Error loading font!" << std::endl;
            return;
        }
    }

    sf::Text text;
    text.setFont(font);
    text.setString("Player Position: (" + std::to_string((int)position.x) + ", " + std::to_string((int)position.y) + ")");
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);

    sf::View currentView = window.getView();
    sf::Vector2f center = currentView.getCenter();
    text.setPosition(center.x - window.getSize().x / 2 + 10.f, center.y - window.getSize().y / 2 + 10.f);

    window.draw(text);
}

void Player::checkCollisionWithWalls(const std::vector<sf::RectangleShape>& walls) {
    sf::Vector2f newPosition;
    if (Physics::checkCollision(player, walls, newPosition)) {
        position = previousPosition;
        player.setPosition(position);
    }
}
void Player::checkCollisionWithMap(const std::vector<sf::Sprite>& bushes) {
    for (const auto& bush : bushes) {
        if (player.getGlobalBounds().intersects(bush.getGlobalBounds())) {
            position = previousPosition;
            player.setPosition(position);
            return;
        }
    }
}

void Player::reset()
{
    heal = maxHp;
    player.setPosition(sf::Vector2f(4850, 5200));
}

void Player::damage(int damages)
{
    heal -= damages;
    if (heal < 0) {
        heal = 0;
    }
}

sf::Vector2f Player::getPosition() const {
    return player.getPosition();
}

float Player::getHealth() const
{
    return heal;
}

float Player::getSpeed() const
{
    return speed;
}

bool Player::isDead() const
{
    return heal <= 0;
}

void Player::setPosition(const sf::Vector2f& position) {
    this->position = position;
    player.setPosition(position);
}