#include "Boss.hpp"
#include <iostream>

void Boss::initSprite()
{
    if (!texture.loadFromFile("assets/images/characters/boss.png")) {
        std::cerr << "Error: Unable to load the Boss texture from " << std::endl;
    }
    sprite.setTexture(texture);
    sprite.setScale(size * 1.2f, size * 1.2f);
}

Boss::Boss(float s, sf::Vector2f p, int hp, int d, float size, Player& refPlayer)
    : Enemy(s, p, hp, d), size(size), speed(s), player(refPlayer), canShoot(false), visionRadius(1000.f) {
    initSprite();
    position = p;
    sprite.setPosition(position);

    // Utiliser les dimensions du sprite après la mise à l'échelle
    sf::FloatRect spriteBounds = sprite.getGlobalBounds();
    hitbox.setSize(sf::Vector2f(spriteBounds.width, spriteBounds.height));
    hitbox.setOrigin(hitbox.getSize() / 2.f);
    hitbox.setFillColor(sf::Color::Transparent);
    hitbox.setOutlineColor(sf::Color::Red);
    hitbox.setOutlineThickness(1.f);
}

void Boss::update(float deltaTime, const std::vector<sf::Sprite>& bushes)
{

    hitbox.setPosition(sprite.getPosition());

    sf::Vector2f playerPos = player.getPosition();
    sf::Vector2f arrowStartPos = sprite.getPosition();
    sf::Vector2f direction = playerPos - arrowStartPos;

    float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    if (distance <= visionRadius) {
        canShoot = true;
    }
    else {
        canShoot = false;
    }

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
    sf::Vector2f playerPos = player.getPosition();
    sf::Vector2f projectileStartPos = sprite.getPosition();
    sf::Vector2f direction = playerPos - projectileStartPos;

    float magnitude = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    if (magnitude != 0) {
        direction /= magnitude;
    }
    projectiles.emplace_back(projectileStartPos, direction, 300.f);
}

sf::FloatRect Boss::getGlobalBounds() const
{
    return hitbox.getGlobalBounds();
}

int Boss::getDamage() const
{
	return damage;
}