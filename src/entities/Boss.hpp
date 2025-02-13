#ifndef BOSS_HPP
#define BOSS_HPP

#include <SFML/Graphics.hpp>
#include "Entity.hpp"
#include "Enemy.hpp"
#include "ProjectilesBoss.hpp"
#include "Player.hpp"
#include <vector>
#include <string>

class Boss : public Enemy {
public:

    Boss(float s, sf::Vector2f p, int hp, int d, float size, Player& refPlayer);

    void update(float deltaTime, const std::vector<sf::Sprite>& bushes) override;
    void draw(sf::RenderWindow& window) override;
    void shoot();

    sf::FloatRect getGlobalBounds() const override;
    void setPath(const std::vector<sf::Vector2f>& points);
    int getDamage() const override;
    void moveToNextPoint(float deltaTime);
protected:
    sf::Sprite sprite;
    sf::Texture texture;
    std::vector<ProjectilesBoss> projectiles;
    Player& player;

    sf::Vector2f position;
    float shootCooldown = 1.0f;
    float timeSinceLastShot = 0.0f;
    float visionRadius;
    bool canShoot;

    float speed;
    float distanceTraveled = 0.f;
    float distanceThreshold;
    int size;
    std::vector<sf::Vector2f> pathPoints;
    int currentPointIndex;
    void initSprite();

private:
    sf::RectangleShape hitbox; 
};

#endif // BOSS_HPP
