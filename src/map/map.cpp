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

    if (!mapElements["fakeBush"].texture.loadFromFile("assets/images/map/textures/bush.png")) {
        std::cerr << "Image Failed to Load : fakeBush.png " << std::endl;
        return;
    }

    if (!mapElements["buttonOFF"].texture.loadFromFile("assets/images/map/textures/buttonOFF.png")) {
        std::cerr << "Image Failed to Load : buttonOFF.png " << std::endl;
        return;
    }

    if (!mapElements["buttonON"].texture.loadFromFile("assets/images/map/textures/buttonON.png")) {
        std::cerr << "Image Failed to Load : buttonON.png " << std::endl;
        return;
    }

    if (!mapElements["torchStandOFF"].texture.loadFromFile("assets/images/map/textures/torchStandOFF.png")) {
        std::cerr << "Image Failed to Load : torchStandOFF.png " << std::endl;
        return;
    }

    if (!mapElements["torchStandON"].texture.loadFromFile("assets/images/map/textures/torchStandON.png")) {
        std::cerr << "Image Failed to Load : torchStandON.png " << std::endl;
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
            else if (pixelColor == sf::Color(255, 247, 0)) {
                sprite.setTexture(mapElements["fakeBush"].texture);
                sprite.setScale(1.f, 1.f);
                sprite.setPosition(x * tileSize, y * tileSize);
                mapElements["fakeBush"].sprites.push_back(sprite);
            }
            else if (pixelColor == sf::Color(0, 8, 255)) {
                sprite.setTexture(mapElements["buttonOFF"].texture);
                sprite.setScale(1.f, 1.f);
                sprite.setPosition(x * tileSize, y * tileSize);
                buttons.push_back({ sprite, false });
            }
            else if (pixelColor == sf::Color(195, 0, 255)) {
                sprite.setTexture(mapElements["torchStandOFF"].texture);
                sprite.setScale(4.f, 4.f);
                sprite.setPosition(x * tileSize, y * tileSize);
                torchStands.push_back({ sprite, false });
            }
        }
    }

    for (size_t i = 0; i < buttons.size(); ++i) {
        buttonTorchPairs.push_back({ i, i });
    }

    addZone(sf::FloatRect(0, 0, 894, 696), "Spawn House");
    addZone(sf::FloatRect(4112, 4108, 2039, 2047), "Zone1"); 
    addZone(sf::FloatRect(2056, 4108, 2048, 2048), "Zone2"); 
    addZone(sf::FloatRect(2056, 6164, 2048, 2048), "Zone3"); 
    addZone(sf::FloatRect(0, 6164, 2039, 2048), "Zone4"); 
    addZone(sf::FloatRect(0, 4108, 2039, 2048), "Zone5"); 
    addZone(sf::FloatRect(2060, 0, 4096, 4096), "Castle Ouside");
    addZone(sf::FloatRect(0, 2212, 1910, 832), "Tunnel 1");
    addZone(sf::FloatRect(0, 3046, 1910, 888), "Tunnel 2");
    addZone(sf::FloatRect(0, 8252, 1010, 1918), "Castle Left");
    addZone(sf::FloatRect(1010, 8252, 2060, 1918), "Castle Middle");
    addZone(sf::FloatRect(3070, 8252, 1520, 1918), "Castle Right");
    addZone(sf::FloatRect(4300, 6280, 1660, 1855), "Castle End Room");

    addDoor(sf::FloatRect(4880, 5192, 60, 20), "Entry House");
    addDoor(sf::FloatRect(415, 610, 60, 20), "Exit House");
    addDoor(sf::FloatRect(1250, 9210, 20, 70), "Entry Castle Door 1");
    addDoor(sf::FloatRect(780, 9210, 20, 70), "Exit Castle Door 1");
    addDoor(sf::FloatRect(1155, 8700, 20, 70), "Entry Castle Door 2");
    addDoor(sf::FloatRect(870, 8700, 20, 70), "Exit Castle Door 2");
    addDoor(sf::FloatRect(2830, 9210, 20, 70), "Entry Castle Door 3");
    addDoor(sf::FloatRect(3300, 9210, 20, 70), "Exit Castle Door 3");
    addDoor(sf::FloatRect(2010, 8385, 70, 20), "Entry Castle Door 4");
    addDoor(sf::FloatRect(5095, 7950, 70, 20), "Exit Castle Door 4");
    addDoor(sf::FloatRect(475, 10085, 70, 20), "Entry Castle Door 5");
    addDoor(sf::FloatRect(3220, 240, 110, 20), "Exit Castle Door 5");
    addDoor(sf::FloatRect(4050, 1080, 110, 20), "Entry Castle Door 6");
    addDoor(sf::FloatRect(2015, 9990, 70, 20), "Exit Castle Door 6");
    addDoor(sf::FloatRect(3550, 10085, 70, 20), "Entry Castle Door 7");
    addDoor(sf::FloatRect(4885, 240, 110, 20), "Exit Castle Door 7");
    addDoor(sf::FloatRect(5650, 648, 52, 48), "Entry Tunnel 1");
    addDoor(sf::FloatRect(350, 2790, 70, 20), "Entry Tunnel 2");
    addDoor(sf::FloatRect(350, 3270, 70, 20), "Exit Tunnel 2");
    addDoor(sf::FloatRect(350, 3850, 70, 20), "Entry Tunnel 3");
    addDoor(sf::FloatRect(4910, 920, 60, 20), "Exit Tunnel 3");
    addDoor(sf::FloatRect(3910, 2620, 400, 20), "Entry Castle Main Door");
    addDoor(sf::FloatRect(3910, 2360, 400, 20), "Exit Castle Main Door");
}

const Map::Zone* Map::getZoneContaining(const sf::Vector2f& position) const {
    for (const auto& zone : zones) {
        if (zone.bounds.contains(position)) {
            return &zone;
        }
    }
    return nullptr;
}

void Map::update(float deltaTime, const sf::FloatRect& playerHitbox) {
    for (size_t i = 0; i < buttonTorchPairs.size(); ++i) {
        auto& button = buttons[buttonTorchPairs[i].first];
        auto& torchStand = torchStands[buttonTorchPairs[i].second];

        if (button.sprite.getGlobalBounds().intersects(playerHitbox)) {
            if (!button.isOn) {
                button.isOn = true;
                button.sprite.setTexture(mapElements["buttonON"].texture);
                torchStand.isOn = true;
                torchStand.sprite.setTexture(mapElements["torchStandON"].texture);
            }
        }
    }
    if (areAllTorchesOn()) {
        std::cout << "Toutes les torches sont allumées !" << std::endl;
    }
}

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
    drawSprites("fakeBush", mapElements, window);

    for (const auto& button : buttons) {
        window.draw(button.sprite);
    }
    for (const auto& torchStand : torchStands) {
        window.draw(torchStand.sprite);
    }
}

void Map::addZone(const sf::FloatRect& bounds, const std::string& name) {
    zones.push_back({ bounds, name });
}

const std::vector<sf::Sprite> Map::getBushes() const {
    std::vector<sf::Sprite> bushes;

    auto it = mapElements.find("bush");
    if (it != mapElements.end()) {
        bushes.insert(bushes.end(), it->second.sprites.begin(), it->second.sprites.end());
    }

    auto fakeIt = mapElements.find("fakeBush");
    if (fakeIt != mapElements.end()) {
        bushes.insert(bushes.end(), fakeIt->second.sprites.begin(), fakeIt->second.sprites.end());
    }

    return bushes;
}

void Map::drawMapHitBox(sf::RenderWindow& window) {
    window.draw(mapHitboxSprite);
}

void Map::addDoor(const sf::FloatRect& bounds, const std::string& name) {
    doors.push_back({ bounds, name });
}

const Map::Door* Map::getDoor(const std::string& name) const {
    for (const auto& door : doors) {
        if (door.name == name) {
            return &door;
        }
    }
    return nullptr;
}

bool Map::areAllTorchesOn() {
    for (const auto& torchStand : torchStands) {
        if (!torchStand.isOn) {
            return false;
        }
    }
    return true;
}