#ifndef KEY_HPP
#define KEY_HPP

#include <SFML/Graphics.hpp>
#include "Item.hpp"

class Key : public Item<int> {
public:
    Key(const std::string& name, const std::string& texturePath, sf::Vector2f position);
    void draw(sf::RenderWindow& window);
    sf::FloatRect getBounds() const;

private:
    sf::Sprite sprite;
    sf::Texture texture;
};

#endif // KEY_HPP