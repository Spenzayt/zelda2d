#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "map.hpp"
#include "Player.hpp"
#include "Bokoblin.hpp"

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

#endif // GAME_H