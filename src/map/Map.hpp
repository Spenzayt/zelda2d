#ifndef MAP_H
#define MAP_H

#include <SFML/Graphics.hpp>
#include "../utils/Config.hpp"
#include "../systems/camera.hpp"
#include <vector>
#include <map>

class Room {
public:
    sf::IntRect rect;
    Room(int x, int y, int width, int height) : rect(x, y, width, height) {}
};

class Map {
private:
    struct MapElement {
        sf::Texture texture;
        std::vector<sf::Sprite> sprites;
    };

    std::map<std::string, MapElement> mapElements;
    std::vector<Room> rooms;
    Camera camera;

public:
    Map();
    ~Map();

    void importAllTextures(sf::RenderWindow& window);
    void loadBackgroundFromImage();
    void update(float deltaTime, const sf::Vector2f& playerPosition);
    void draw(sf::RenderWindow& window);

    const std::vector<sf::Sprite>& getTrees() const;
    const std::vector<sf::Sprite>& getBushes() const;
};

#endif // MAP_H
