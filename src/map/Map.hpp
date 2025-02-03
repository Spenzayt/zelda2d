#ifndef MAP_H
#define MAP_H

#include <SFML/Graphics.hpp>
#include "../utils/Config.hpp"
#include <vector>
#include <map>

class Map {
private:
    struct MapElement {
        sf::Texture texture;
        std::vector<sf::Sprite> sprites;
    };

    std::map<std::string, MapElement> mapElements;

public:
    struct Zone {
        sf::FloatRect bounds;
        std::string name;
    };

private:
    std::vector<Zone> zones;

public:
    Map();
    ~Map();

    void importAllTextures(sf::RenderWindow& window);
    void loadBackgroundFromImage();
    void update(float deltaTime);
    void draw(sf::RenderWindow& window);

    const std::vector<sf::Sprite>& getBushes() const;

    const Zone* getZoneContaining(const sf::Vector2f& position) const;
    void addZone(const sf::FloatRect& bounds, const std::string& name);
};

#endif // MAP_H