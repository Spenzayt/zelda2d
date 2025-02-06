#include "../entities/Enemy.hpp"
#include <iostream>

Enemy::Enemy(float s, sf::Vector2f p, int hp, int d) : speed(s), position(p), heal(hp), damage(d) {}
void Enemy::takeDamage(int dmg) {
    heal -= dmg;
    if (heal <= 0) {
        std::cout << "Enemy defeated!" << std::endl;
    }
}

bool Enemy::isAlive() const {
    return heal > 0;
}

bool Enemy::isDead() const {
    return heal <= 0;
}

