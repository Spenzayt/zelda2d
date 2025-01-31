#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include "../map/Map.hpp"
#include "../entities/Player.hpp"
#include "../entities/Bokoblin.hpp"

class Map;
class Player;
class Patrolling;

class Game {
public:
    Game();
    ~Game();

    void run();

private:
    void createWindow();
    void processEvents();
    void update(float deltaTime);
    void render();

    sf::RenderWindow window;
    bool isRunning;

    Map map;
    Player player;
    Patrolling bokoblin;
};

#endif // GAME_HPP