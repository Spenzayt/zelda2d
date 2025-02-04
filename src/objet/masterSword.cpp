#include "MasterSword.hpp"
#include <iostream>

Sword::Sword(sf::Vector2f position) : Item("MasterSword", 1) {
    if (!texture.loadFromFile("assets\\images\\Item\\MasterSword.png")) {
        std::cerr << "Erreur chargement de l'image de l'épée !" << std::endl;
    }
    sprite.setTexture(texture);
    sprite.setPosition(position);
    sprite.setScale(0.15f, 0.15f); 
}

void Sword::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

sf::FloatRect Sword::getBounds() const {
    return sprite.getGlobalBounds();
}
