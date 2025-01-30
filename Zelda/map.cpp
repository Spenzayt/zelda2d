#include "map.hpp"
#include <iostream>

Map::Map() {}

Map::~Map() {}

void Map::importAllTextures() {
    if (!backgroundImage.loadFromFile("assets/map/map_test.png")) {
        std::cerr << "Image Failed to Load : map_test.png " << std::endl;
        return;
    }
    if (!grassTexture.loadFromFile(Config::TEXTURE_PATH + "grass.png")) {
        std::cerr << "Image Failed to Load : grass.png " << std::endl;
        return;
    }
    if (!dirtTexture.loadFromFile(Config::TEXTURE_PATH + "dirt.png")) {
        std::cerr << "Image Failed to Load : dirt.png " << std::endl;
        return;
    }
    if (!bushTexture.loadFromFile(Config::TEXTURE_PATH + "bush.png")) {
        std::cerr << "Image Failed to Load : bush.png " << std::endl;
        return;
    }
    if (!treeTexture.loadFromFile(Config::TEXTURE_PATH + "tree.png")) {
        std::cerr << "Image Failed to Load : tree.png " << std::endl;
        return;
    }
}

void Map::loadBackgroundFromImage() {
    unsigned int width = backgroundImage.getSize().x;
    unsigned int height = backgroundImage.getSize().y;

    for (unsigned int x = 0; x < width; x++) {
        for (unsigned int y = 0; y < height; y++) {
            sf::Color pixelColor = backgroundImage.getPixel(x, y);
            sf::Sprite sprite;

            if (pixelColor == sf::Color(0, 141, 0)) {
                sprite.setTexture(grassTexture);
                sprite.setScale(0.5f, 0.5f);
                sprite.setPosition(x * Config::TILE_SIZE, y * Config::TILE_SIZE);
                grassSpriteVector.push_back(sprite);
            }
            else if (pixelColor == sf::Color(150, 75, 0)) {
                sprite.setTexture(dirtTexture);
                sprite.setScale(0.5f, 0.5f);
                sprite.setPosition(x * Config::TILE_SIZE, y * Config::TILE_SIZE);
                dirtSpriteVector.push_back(sprite);
            }
            else if (pixelColor == sf::Color(0, 92, 0)) {
                sprite.setTexture(bushTexture);
                sprite.setScale(0.5f, 0.5f);
                sprite.setPosition(x * Config::TILE_SIZE, y * Config::TILE_SIZE);
                bushSpriteVector.push_back(sprite);
            }
            else if (pixelColor == sf::Color(255, 0, 0)) {
                sprite.setTexture(treeTexture);
                sprite.setScale(160.f / treeTexture.getSize().x, 200.f / treeTexture.getSize().y);
                float offsetX = (Config::TILE_SIZE - 160.f) / 2.0f;
                float offsetY = (Config::TILE_SIZE - 200.f) / 2.0f;
                sprite.setPosition(x * Config::TILE_SIZE + offsetX, y * Config::TILE_SIZE + offsetY);
                treeSpriteVector.push_back(sprite);
            }
            sprite.setPosition(x * Config::TILE_SIZE, y * Config::TILE_SIZE);
        }
    }
}

void Map::update(float deltaTime) {
    // update
}

void Map::draw(sf::RenderWindow& window) {
    for (auto& sprite : grassSpriteVector) window.draw(sprite);
    for (auto& sprite : dirtSpriteVector) window.draw(sprite);
    for (auto& sprite : bushSpriteVector) window.draw(sprite);
    for (auto& sprite : treeSpriteVector) window.draw(sprite);
}