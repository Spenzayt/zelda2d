#pragma once
#ifndef MASTERSWORD_HPP
#define MASTERSWORD_HPP

#include <SFML/Graphics.hpp>
#include "Item.hpp"

class Sword : public Item<int> {
public:
    Sword(sf::Vector2f position);
    void draw(sf::RenderWindow& window);
    sf::FloatRect getBounds() const;

private:
    sf::Sprite sprite;
    sf::Texture texture;
};

#endif // SWORD_HPP
