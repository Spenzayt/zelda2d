#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.hpp"

class Player : public Entity
{
public:
    Player(sf::Vector2f position, float size, const std::string& texturePath);

    void update(float deltatime, const std::vector<sf::Sprite>& trees, const std::vector<sf::Sprite>& bushes) override;
    void draw(sf::RenderWindow& window) override;
    void handleInput(float deltatime);
    void increaseSpeed(float amount);
    void collectKey();
    void checkCollisionWithWalls(const std::vector<sf::RectangleShape>& walls);
    void checkCollisionWithMap(const std::vector<sf::Sprite>& trees, const std::vector<sf::Sprite>& bushes);


    const sf::Sprite& getSprite() const { return player; }
    bool hasKey;

    sf::Vector2f getPosition() const;

protected:
    sf::Sprite player;
    sf::Texture texture;
    sf::Vector2f previousPosition;
};
