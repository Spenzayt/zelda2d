#include "../entities/Bokoblin.hpp"
#include <cmath>
#include <iostream>

void Bokoblin::initSprite()
{
    if (!texture.loadFromFile("assets/images/characters/premierEnnemi.png")) {
        std::cerr << "Error: Unable to load the Bokoblin texture from " << std::endl;
    }
}

void Bokoblin::initTexture()
{
    sprite.setTexture(texture);
}

Bokoblin::Bokoblin(float s, sf::Vector2f p, int hp, int d, float size) : Enemy(s, p, hp, d), size(size), speed(s)
{
    initSprite();
    initTexture();

    currentPointIndex = 0;
    distanceThreshold = 5.f;

    position = p;
    sprite.setPosition(position);
    sprite.setScale(size *0.4f, size *0.4f);
    
}

void Bokoblin::update(float deltaTime, const std::vector<sf::Sprite>& bushes) {
  

    moveToNextPoint(deltaTime);

}

void Bokoblin::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

void Bokoblin::setPath(const std::vector<sf::Vector2f>& points)
{
    pathPoints = points;
    currentPointIndex = 0;
}

sf::FloatRect Bokoblin::getGlobalBounds() const
{
    return sprite.getGlobalBounds();
}

int Bokoblin::getDamage() const
{
    return damage;
}

void Bokoblin::moveToNextPoint(float deltaTime) {
    if (pathPoints.empty()) return;

    sf::Vector2f target = pathPoints[currentPointIndex];
    sf::Vector2f direction = target - position;

    float magnitude = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    if (magnitude <= distanceThreshold) {
        currentPointIndex = (currentPointIndex + 1) % pathPoints.size();
    }
    else {
        direction /= magnitude;
        position += direction * speed;
        sprite.setPosition(position);
    }

}

