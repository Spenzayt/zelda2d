#ifndef BOSS_HPP
#define BOSS_HPP

#include <SFML/Graphics.hpp>
#include "Entity.hpp"
#include "Enemy.hpp"
#include <vector>
#include <string>

class Boss : public Enemy {
public:

    Boss(float s, sf::Vector2f p, int hp, int d, float size);

    void update(float deltaTime, const std::vector<sf::Sprite>& bushes) override;
    void draw(sf::RenderWindow& window) override;

    sf::FloatRect getGlobalBounds() const override;
    int getDamage() const override;
    const sf::Sprite& getSprite() const { return sprite; }

protected:
    sf::Sprite sprite;
    sf::Texture texture;
    std::vector<sf::Vector2f> pathPoints;
    int currentPointIndex;
    float distanceThreshold;
    int size;
    
    void initSprite();
    void initTexture();
    float speed;

};

#endif // BOSS_HPP
