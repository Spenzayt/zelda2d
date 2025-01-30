#ifndef GAME_H
#define GAME_H
#include "Player.hpp"

#include <SFML/Graphics.hpp>

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

    Player player;
};

#endif // GAME_H