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
    };

    void importAllTextures(sf::RenderWindow& window);
    void loadBackgroundFromImage();
    void update(float deltaTime);
    void draw(sf::RenderWindow& window);

    const Zone* getZoneContaining(const sf::Vector2f& position) const;
    void addZone(const sf::FloatRect& bounds, const std::string& name);

    const std::vector<sf::Sprite>& getBushes() const;
    void drawMapHitBox(sf::RenderWindow& window);

    const sf::FloatRect& getHouseEntry() const;
    const sf::FloatRect& getHouseExit() const;

private:
    sf::Texture mapHitboxTexture;
    sf::Sprite mapHitboxSprite;

    struct MapElement {
        sf::Texture texture;
        std::vector<sf::Sprite> sprites;
    };

    std::map<std::string, MapElement> mapElements;
    std::vector<Zone> zones;

    sf::FloatRect houseEntry;
    sf::FloatRect houseExit;
};

#endif // MAP_H