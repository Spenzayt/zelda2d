#include "Bokoblin.hpp"
#include <cmath>
#include <iostream>

Patrolling::Patrolling(const sf::Vector2f& startPosition, float size, const std::vector<sf::Vector2f>& path, const std::string& texturePath)
    : pathPoints(path), currentPointIndex(0), distanceThreshold(5.0f) {
    position = startPosition;

    damage = 5;
    heal = 50;
    speed = 150;
    if (!texture.loadFromFile(texturePath)) {
        std::cerr << "Erreur: Impossible de charger la texture du Bokoblin depuis " << texturePath << std::endl;
    }

    sprite.setTexture(texture);
    sprite.setScale(size / texture.getSize().x, size / texture.getSize().y);
    sprite.setPosition(position);
}

void Patrolling::update(float deltatime, const std::vector<sf::Sprite>& trees, const std::vector<sf::Sprite>& bushes)
{
    if (!pathPoints.empty())
    {
        moveToNextPoint(deltatime);
    }
    sprite.setPosition(position);
}

void Patrolling::draw(sf::RenderWindow& window)
{
    window.draw(sprite);
}

void Patrolling::moveToNextPoint(float deltatime)
{
    sf::Vector2f target = pathPoints[currentPointIndex];
    sf::Vector2f direction = target - position;

    float magnitude = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    if (magnitude <= distanceThreshold)
    {
        currentPointIndex = (currentPointIndex + 1) % pathPoints.size();
    }
    else
    {
        direction.x /= magnitude;
        direction.y /= magnitude;

        position.x += direction.x * speed * deltatime;
        position.y += direction.y * speed * deltatime;
    }
}
