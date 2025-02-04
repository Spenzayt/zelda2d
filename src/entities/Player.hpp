#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.hpp"

class Player : public Entity
{
public:
    Player(sf::Vector2f position, float size, const std::string& texturePath, float hp);

    void update(float deltatime, const std::vector<sf::Sprite>& bushes) override;
    void draw(sf::RenderWindow& window) override;
    void handleInput(float deltatime);
    void increaseSpeed(float amount);
    void collectKey();
    void checkCollisionWithWalls(const std::vector<sf::RectangleShape>& walls);
    void checkCollisionWithMap(const std::vector<sf::Sprite>& bushes);

    const sf::Sprite& getSprite() const { return player; }
    bool hasKey;
    
    void reset();

    void damage(int damages);

    sf::Vector2f getPosition() const;
    float getHealth() const;
    float getSpeed() const;
    bool isDead() const;


    void setPosition(const sf::Vector2f& position);
    //id setSpeed(int speed);


protected:
    sf::Sprite player;
    sf::Texture texture;
    sf::Vector2f previousPosition;

    int maxHp;
};