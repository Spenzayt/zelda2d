#include "map.hpp"
#include <iostream>

Map::Map() : camera(Config::WINDOW_WIDTH, Config::WINDOW_HEIGHT) {
    std::vector<sf::IntRect> rooms = {
        /*{0, 0, 960, 540},
        {960, 0, 1920, 540},
        {0, 540, 960, 1080},
        {960, 540, 1920, 1080},*/
    };
    camera.setRooms(rooms);
}

Map::~Map() {}

void Map::importAllTextures(sf::RenderWindow& window) {
    if (!backgroundImage.loadFromFile("assets/map/map.png")) {
        std::cerr << "Image Failed to Load : map_test.png " << std::endl;
        return;
    }
    if (!backgroundTexture.loadFromFile("assets/map/map.png")) {
        std::cerr << "Image Failed to Load : map.png " << std::endl;
        return;
    }
    if (!grassTexture.loadFromFile("assets/map/map.png")) {
        std::cerr << "Image Failed to Load : map.png " << std::endl;
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

    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setScale(4.f, 4.f);
    backgroundSprite.setPosition(0.f, 0.f);
}

void Map::loadBackgroundFromImage() {
    unsigned int width = backgroundImage.getSize().x;
    unsigned int height = backgroundImage.getSize().y;

    for (unsigned int x = 0; x < width; x++) {
        for (unsigned int y = 0; y < height; y++) {
            sf::Color pixelColor = backgroundImage.getPixel(x, y);
            sf::Sprite sprite;

            if (pixelColor == sf::Color(0, 255, 0)) {
                sprite.setTexture(bushTexture);
                sprite.setScale(1.f, 1.f);
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

void Map::update(float deltaTime, const sf::Vector2f& playerPosition) {
    camera.update(playerPosition, deltaTime);
}

void Map::draw(sf::RenderWindow& window) {
    window.draw(backgroundSprite);

    for (auto& sprite : grassSpriteVector) window.draw(sprite);
    for (auto& sprite : dirtSpriteVector) window.draw(sprite);
    for (auto& sprite : bushSpriteVector) window.draw(sprite);
    for (auto& sprite : treeSpriteVector) window.draw(sprite);

    camera.applyView(window);
}