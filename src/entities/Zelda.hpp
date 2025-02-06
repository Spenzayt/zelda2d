#ifndef ZELDA_HPP
#define ZELDA_HPP

#include <SFML/Graphics.hpp>
#include "../src/entities/Entity.hpp"

class Zelda : public Entity {
public:
    Zelda(sf::Vector2f position, float size, const std::string& texturePath);

    void update(float deltaTime, const std::vector<sf::Sprite>& bushes) override;
    void draw(sf::RenderWindow& window) override;

    sf::FloatRect getGlobalBounds() const;

private:
    sf::Sprite zelda;
    sf::Texture texture;
};

#endif // ZELDA_HPP