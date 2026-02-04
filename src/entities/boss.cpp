#include "Boss.hpp"
#include <iostream>
#include <cmath>

void Boss::initSprite()
{
    if (!texture.loadFromFile("assets/images/characters/boss.png")) {
        std::cerr << "Error: Unable to load the Boss texture" << std::endl;
    }
    sprite.setTexture(texture);
    sprite.setScale(size * 1.2f, size * 1.2f);

    // Hitbox
    sf::FloatRect spriteBounds = sprite.getGlobalBounds();
    hitbox.setSize(sf::Vector2f(spriteBounds.width, spriteBounds.height));
    hitbox.setOrigin(hitbox.getSize() / 2.f);
    hitbox.setFillColor(sf::Color::Transparent);
    hitbox.setOutlineColor(sf::Color::Red);
    hitbox.setOutlineThickness(1.f);
}

Boss::Boss(float s, sf::Vector2f p, int hp, int d, float size, Player& refPlayer)
    : Enemy(s, p, hp, d), size(size), speed(s), player(refPlayer)
{
    initSprite();
    position = p;
    sprite.setPosition(position);
}

void Boss::update(float deltaTime, const std::vector<sf::Sprite>& bushes)
{
    hitbox.setPosition(sprite.getPosition());

    moveToNextPoint(deltaTime);

    sf::Vector2f playerPos = player.getPosition();
    sf::Vector2f direction = playerPos - sprite.getPosition();
    float distance = std::hypot(direction.x, direction.y);

    canShoot = distance <= visionRadius;

    if (canShoot) {
        timeSinceLastShot += deltaTime;
        if (timeSinceLastShot >= shootCooldown) {
            shoot();
            timeSinceLastShot = 0.f;
        }
    }

    for (size_t i = 0; i < projectiles.size(); i++) {
        projectiles[i].update(deltaTime);

        if (projectiles[i].getGlobalBounds().intersects(player.getGlobalBounds())) {
            player.damage(getDamage());
            projectiles.erase(projectiles.begin() + i);
            i--;
            continue;
        }

        float traveledDistance = std::hypot(
            projectiles[i].getPosition().x - projectiles[i].getStartPosition().x,
            projectiles[i].getPosition().y - projectiles[i].getStartPosition().y
        );

        if (traveledDistance > projectiles[i].getMaxDistance()) {
            projectiles.erase(projectiles.begin() + i);
            i--;
        }
    }
}

void Boss::draw(sf::RenderWindow& window)
{
    window.draw(sprite);
    for (auto& projectile : projectiles) {
        projectile.draw(window);
    }
}

void Boss::shoot()
{
    sf::Vector2f dir = player.getPosition() - sprite.getPosition();
    float mag = std::hypot(dir.x, dir.y);
    if (mag != 0) dir /= mag;

    projectiles.emplace_back(sprite.getPosition(), dir, 300.f);
}

sf::FloatRect Boss::getGlobalBounds() const
{
    return hitbox.getGlobalBounds();
}

void Boss::setPath(const std::vector<sf::Vector2f>& points)
{
    pathPoints = points;
    currentPointIndex = 0;
}

int Boss::getDamage() const
{
    return damage;
}

void Boss::moveToNextPoint(float deltaTime)
{
    if (pathPoints.empty()) return;

    sf::Vector2f target = pathPoints[currentPointIndex];
    sf::Vector2f dir = target - position;
    float mag = std::hypot(dir.x, dir.y);

    if (mag <= distanceThreshold) {
        currentPointIndex = (currentPointIndex + 1) % pathPoints.size();
    }
    else {
        dir /= mag;
        position += dir * speed * deltaTime;
        sprite.setPosition(position);
    }
}