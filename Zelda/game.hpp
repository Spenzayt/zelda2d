#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "map.hpp"
#include "Player.hpp"
#include "Menu.hpp"
#include "MainMenu.hpp"
#include "PauseMenu.hpp"
#include "OptionsMenu.hpp"

class Game {
public:
    enum GameState {
        MAIN_MENU,
        PLAYING,
        PAUSE,
        VICTORY,
        GAMEOVER,
        OPTIONS
    };
    Game();
    ~Game();

    void run();
    void handleGameState(Event& event);
    void drawPauseMenu();
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
    OptionsMenu optionsMenu;

    RectangleShape overlay;

    bool ignoreNextClick;
    bool isGamePaused;
};

#endif // GAME_H