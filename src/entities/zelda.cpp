#include "zelda.hpp"
#include <iostream>

Zelda::Zelda(sf::Vector2f spawnposition, float size, const std::string& texturePath) {
    if (!texture.loadFromFile(texturePath)) {
        std::cerr << "Error loading texture from: " << texturePath << std::endl;
    }
    zelda.setTexture(texture);
    zelda.setScale(size / static_cast<float>(texture.getSize().x), size / static_cast<float>(texture.getSize().y));
    sf::FloatRect bounds = zelda.getLocalBounds();
    zelda.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);
    zelda.setPosition(spawnposition);
}

void Zelda::update(float deltaTime, const std::vector<sf::Sprite>& bushes) {}

void Zelda::draw(sf::RenderWindow& window) {
    window.draw(zelda);
}

sf::FloatRect Zelda::getGlobalBounds() const {
    return zelda.getGlobalBounds();
}