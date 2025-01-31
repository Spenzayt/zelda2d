#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.hpp"
#include <vector>

class Patrolling : public Entity
{
public:
    Patrolling(const sf::Vector2f& startPosition, float size, const std::vector<sf::Vector2f>& path, const std::string& texturePath);


    void update(float deltatime, const std::vector<sf::Sprite>& trees, const std::vector<sf::Sprite>& bushes) override;
    void draw(sf::RenderWindow& window) override;
    const sf::Sprite& getSprite() const { return sprite; }

protected:
    sf::Sprite sprite;
    sf::Texture texture;
    std::vector<sf::Vector2f> pathPoints;
    int currentPointIndex;
    float distanceThreshold;

    void moveToNextPoint(float deltatime);
};