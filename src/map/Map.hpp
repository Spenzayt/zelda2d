#ifndef MAP_H
#define MAP_H

#include <SFML/Graphics.hpp>
#include "../utils/Config.hpp"
#include <vector>
#include <map>

class Map {
public:
    Map();
    ~Map();

    struct Zone {
        sf::FloatRect bounds;
        std::string name;

        std::string getName() const {
            return name;
        }
    };

    struct Door {
        sf::FloatRect bounds;
        std::string name;
    };

    struct Button {
        sf::Sprite sprite;
        bool isOn;
    };

    struct TorchStand {
        sf::Sprite sprite;
        bool isOn;
    };

    void importAllTextures(sf::RenderWindow& window);
    void loadBackgroundFromImage();
    void update(float deltaTime, const sf::FloatRect& playerHitbox);
    void draw(sf::RenderWindow& window);

    const Zone* getZoneContaining(const sf::Vector2f& position) const;
    void addZone(const sf::FloatRect& bounds, const std::string& name);

    const std::vector<sf::Sprite> getBushes() const;
    void drawMapHitBox(sf::RenderWindow& window);

    void addDoor(const sf::FloatRect& bounds, const std::string& name);
    const Door* getDoor(const std::string& name) const;
    bool areAllTorchesOn();

    std::vector<Door> doors;

private:
    sf::Texture mapHitboxTexture;
    sf::Sprite mapHitboxSprite;

    struct MapElement {
        sf::Texture texture;
        std::vector<sf::Sprite> sprites;
    };

    std::map<std::string, MapElement> mapElements;
    std::vector<Zone> zones;
    std::vector<Button> buttons;
    std::vector<TorchStand> torchStands;
    std::vector<std::pair<int, int>> buttonTorchPairs;
};

#endif // MAP_H