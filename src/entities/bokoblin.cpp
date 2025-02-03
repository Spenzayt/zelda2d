#include "../entities/Bokoblin.hpp"
#include <cmath>
#include <iostream>

void Bokoblin::initSprite()
{
    if (!texture.loadFromFile("assets/images/characters/Link.png")) {
        std::cerr << "Error: Unable to load the Bokoblin texture from " << std::endl;
    }
}

void Bokoblin::initTexture()
{
    sprite.setTexture(texture);
}

Bokoblin::Bokoblin(float s, sf::Vector2f p, int hp, int d, float size) : Enemy(s, p, hp, d), size(size)
{
    initSprite();
    initTexture();

    position = p;
    sprite.setScale(size / texture.getSize().x, size / texture.getSize().y);
    sprite.setPosition(position);

}

void Bokoblin::update(float deltaTime, const std::vector<sf::Sprite>& bushes) {
    if (!pathPoints.empty()) {
        moveToNextPoint(deltaTime);
    }
    sprite.setPosition(position);
}

void Bokoblin::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

void Bokoblin::moveToNextPoint(float deltaTime) {
    sf::Vector2f target = pathPoints[currentPointIndex];
    sf::Vector2f direction = target - position;

    float magnitude = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    if (magnitude <= distanceThreshold) {
        currentPointIndex = (currentPointIndex + 1) % pathPoints.size();
    }
    else {
        direction /= magnitude;

        position += direction * (speed * deltaTime);
    }
}

