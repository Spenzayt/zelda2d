#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.hpp"
#include "../core/InputHandler.hpp"
#include "../systems/Physics.hpp"

class Player : public Entity
{
public:
    Player(sf::Vector2f position, float size, const std::string& texturePath, float hp);

    enum PlayerLocation {
        OUTSIDE,
        INSIDE_HOUSE,
        INSIDE_CASTLE
    };

    void update(float deltatime, const std::vector<sf::Sprite>& bushes) override;
    void draw(sf::RenderWindow& window) override;
    void handleInput(float deltatime);
    void increaseSpeed(float amount);
    sf::Vector2f getMovementDelta(float deltatime) const;
    void collectKey();
    void checkCollisionWithWalls(const std::vector<sf::RectangleShape>& walls);
    void checkCollisionWithMap(const std::vector<sf::Sprite>& bushes);
    void checkHouseEntry(const sf::FloatRect& houseEntry, PlayerLocation& location);
    void checkHouseExit(const sf::FloatRect& houseExit, PlayerLocation& location);

    const sf::Sprite& getSprite() const { return player; }
    bool hasKey;
    
    void reset();

    void damage(int damages);

    sf::Vector2f getPosition() const;
    float getHealth() const;
    float getSpeed() const;
    sf::FloatRect getGlobalBounds() const;
    bool isDead() const;

    void setPosition(const sf::Vector2f& position);

    //id setSpeed(int speed);

    sf::FloatRect getHitbox() const;
    void drawHitBox(sf::RenderWindow& window);

protected:
    sf::Sprite player;
    sf::Texture texture;
    sf::Vector2f previousPosition;
    
    int maxHp;
    float damageCooldown;

    Physics physics;
    sf::FloatRect hitbox;

};