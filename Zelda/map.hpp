#ifndef MAP_H
#define MAP_H

#include <SFML/Graphics.hpp>
#include "config.hpp"
#include "camera.hpp"
#include <vector>

class Room {
public:
    sf::IntRect rect;
    Room(int x, int y, int width, int height) : rect(x, y, width, height) {}
};

class Map {
private:
    sf::Image backgroundImage;

    sf::Texture grassTexture;
    sf::Sprite grassSprite;

    sf::Texture dirtTexture;
    sf::Sprite dirtSprite;

    sf::Texture bushTexture;
    sf::Sprite bushSprite;

    sf::Texture treeTexture;
    sf::Sprite treeSprite;

    std::vector<sf::Sprite> grassSpriteVector;
    std::vector<sf::Sprite> dirtSpriteVector;
    std::vector<sf::Sprite> bushSpriteVector;
    std::vector<sf::Sprite> treeSpriteVector;
    std::vector<Room> rooms;

    Camera camera;

public:
    Map();
    ~Map();

    void importAllTextures();
    void loadBackgroundFromImage();
    void update(float deltaTime, const sf::Vector2f& playerPosition);
    void draw(sf::RenderWindow& window);
    const std::vector<sf::Sprite>& getTrees() const { return treeSpriteVector; }
    const std::vector<sf::Sprite>& getBushes() const { return bushSpriteVector; }

};

#endif // MAP_H