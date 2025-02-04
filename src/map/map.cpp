#include "Map.hpp"
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

    if (!mapElements["grass"].texture.loadFromFile("assets/images/map/textures/grass.png")) {
        std::cerr << "Image Failed to Load : grass.png " << std::endl;
        return;
    }

    if (!mapHitboxTexture.loadFromFile("assets/images/map/collision_map.png")) {
        std::cerr << "Image Failed to Load : collision_map.png " << std::endl;
        return;
    }

    mapElements["background"].sprites.push_back(sf::Sprite(mapElements["background"].texture));
    mapElements["background"].sprites[0].setScale(4.f, 4.f);
    mapElements["background"].sprites[0].setPosition(0.f, 0.f);

    if (mapElements["background"].sprites.empty()) {
        std::cerr << "Error: Background sprite not added correctly." << std::endl;
    }

    mapHitboxSprite.setTexture(mapHitboxTexture);
    mapHitboxSprite.setScale(4.f, 4.f);

    houseEntry = sf::FloatRect(4880, 5192, 60, 20);
    houseExit = sf::FloatRect(415, 610, 60, 20);
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
        }
    }
    addZone(sf::FloatRect(4112, 4108, 2039, 2047), "Zone1"); 
    addZone(sf::FloatRect(2056, 4108, 2048, 2048), "Zone2"); 
    addZone(sf::FloatRect(2056, 6164, 2048, 2048), "Zone3"); 
    addZone(sf::FloatRect(0, 6164, 2039, 2048), "Zone4"); 
    addZone(sf::FloatRect(0, 4108, 2039, 2048), "Zone5"); 
    addZone(sf::FloatRect(2060, 0, 4096, 4096), "Zone6");
}

const Map::Zone* Map::getZoneContaining(const sf::Vector2f& position) const {
    for (const auto& zone : zones) {
        if (zone.bounds.contains(position)) {
            return &zone;
        }
    }
    return nullptr;
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
}

void Map::addZone(const sf::FloatRect& bounds, const std::string& name) {
    zones.push_back({ bounds, name });
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

void Map::drawMapHitBox(sf::RenderWindow& window) {
    window.draw(mapHitboxSprite);
}

const sf::FloatRect& Map::getHouseEntry() const {
    return houseEntry;
}

const sf::FloatRect& Map::getHouseExit() const {
    return houseExit;
}