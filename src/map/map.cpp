#include "map.hpp"
#include <iostream>

Map::Map() {}

Map::~Map() {}

void Map::importAllTextures(sf::RenderWindow& window) {
    if (!mapElements["background"].texture.loadFromFile("assets/images/map/map.png")) {
        std::cerr << "Image Failed to Load : map.png " << std::endl;
        return;
    }

    if (!mapElements["bush"].texture.loadFromFile("assets/images/map/textures/bush.png")) {
        std::cerr << "Image Failed to Load : bush.png " << std::endl;
        return;
    }

    if (!mapElements["tree"].texture.loadFromFile("assets/images/map/textures/tree.png")) {
        std::cerr << "Image Failed to Load : tree.png " << std::endl;
        return;
    }

    if (!mapElements["grass"].texture.loadFromFile("assets/images/map/textures/grass.png")) {
        std::cerr << "Image Failed to Load : grass.png " << std::endl;
        return;
    }

    mapElements["background"].sprites.push_back(sf::Sprite(mapElements["background"].texture));
    mapElements["background"].sprites[0].setScale(4.f, 4.f);
    mapElements["background"].sprites[0].setPosition(0.f, 0.f);

    if (mapElements["background"].sprites.empty()) {
        std::cerr << "Error: Background sprite not added correctly." << std::endl;
    }
}

void Map::loadBackgroundFromImage() {
    sf::Image backgroundImage;
    if (!backgroundImage.loadFromFile("assets/images/map/map.png")) {
        std::cerr << "Image Failed to Load : map.png " << std::endl;
        return;
    }

    unsigned int width = backgroundImage.getSize().x;
    unsigned int height = backgroundImage.getSize().y;
    float tileSize = Config::TILE_SIZE;

    for (unsigned int x = 0; x < width; x++) {
        for (unsigned int y = 0; y < height; y++) {
            sf::Color pixelColor = backgroundImage.getPixel(x, y);
            sf::Sprite sprite;

            if (pixelColor == sf::Color(0, 255, 0)) {
                sprite.setTexture(mapElements["bush"].texture);
                sprite.setScale(1.f, 1.f);
                sprite.setPosition(x * tileSize, y * tileSize);
                mapElements["bush"].sprites.push_back(sprite);
            }
            else if (pixelColor == sf::Color(255, 0, 0)) {
                sprite.setTexture(mapElements["tree"].texture);
                sprite.setScale(160.f / mapElements["tree"].texture.getSize().x, 200.f / mapElements["tree"].texture.getSize().y);
                float offsetX = (tileSize - 160.f) / 2.0f;
                float offsetY = (tileSize - 200.f) / 2.0f;
                sprite.setPosition(x * tileSize + offsetX, y * tileSize + offsetY);
                mapElements["tree"].sprites.push_back(sprite);
            }
        }
    }
}

void Map::update(float deltaTime) {}

void Map::draw(sf::RenderWindow& window) {
    if (mapElements.find("background") != mapElements.end() && !mapElements["background"].sprites.empty()) {
        window.draw(mapElements["background"].sprites[0]);
    }
    else {
        std::cerr << "Error: 'background' key not found in mapElements during draw." << std::endl;
    }

    auto drawSprites = [](const std::string& key, std::map<std::string, MapElement>& elements, sf::RenderWindow& window) {
        auto it = elements.find(key);
        if (it != elements.end()) {
            for (auto& sprite : it->second.sprites) {
                window.draw(sprite);
            }
        }
        else {
            std::cerr << "Error: Key '" << key << "' not found in mapElements." << std::endl;
        }
    };

    drawSprites("grass", mapElements, window);
    drawSprites("bush", mapElements, window);
    drawSprites("tree", mapElements, window);
}

const std::vector<sf::Sprite>& Map::getTrees() const {
    auto it = mapElements.find("tree");
    if (it != mapElements.end()) {
        return it->second.sprites;
    }
    else {
        static std::vector<sf::Sprite> empty;
        return empty;
    }
}

const std::vector<sf::Sprite>& Map::getBushes() const {
    auto it = mapElements.find("bush");
    if (it != mapElements.end()) {
        return it->second.sprites;
    }
    else {
        static std::vector<sf::Sprite> empty;
        return empty;
    }
}