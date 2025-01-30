#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "map.hpp"
#include "Player.hpp"
#include "Menu.hpp"
#include "MainMenu.hpp"
#include "PauseMenu.hpp"

class Game {
public:
    enum GameState {
        MAIN_MENU,
        PLAYING,
        PAUSE,
        VICTORY,
        GAMEOVER
    };
    Game();
    ~Game();

    void run();
    void handleGameState(Event& event);

private:
    void createWindow();
    void processEvents();
    void update(float deltaTime);
    void render();

    sf::RenderWindow window;
    bool isRunning;

    Map map;
    Player player;

    // etats du jeu
    GameState currentState;
    MainMenu mainMenu;
    PauseMenu pauseMenu;

    RectangleShape overlay;
    void drawPauseMenu();
};

#endif // GAME_H