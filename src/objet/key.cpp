#include "Key.hpp"
#include <iostream>

Key::Key(const std::string& name, const std::string& texturePath, sf::Vector2f position)
    : Item(name, 1) {
    if (!texture.loadFromFile(texturePath)) {
        std::cerr << "Image Failed to Load : " << texturePath << std::endl;
    }
    sprite.setTexture(texture);
    sprite.setPosition(position);
    sprite.setScale(0.2f, 0.2f);
}

void Key::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

sf::FloatRect Key::getBounds() const {
    return sprite.getGlobalBounds();
}