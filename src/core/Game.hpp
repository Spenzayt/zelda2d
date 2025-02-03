#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include "../map/Map.hpp"
#include "../entities/Player.hpp"
#include "../entities/Bokoblin.hpp"
#include "../ui/Menu.hpp"
#include "../ui/MainMenu.hpp"
#include "../ui/PauseMenu.hpp"
#include "../ui/OptionsMenu.hpp"
#include "../systems/camera.hpp"
#include "../systems/KonamiCode.hpp"

class Map;
class Player;
class Patrolling;

class Game {
public:
    Game();
    ~Game();

    enum GameState {
        MAIN_MENU,
        PLAYING,
        PAUSE,
        VICTORY,
        GAMEOVER,
        OPTIONS
    };

    void run();
    void handleGameState(sf::Event& event);
    void drawPauseMenu();

    bool godMode;
    bool noclip;
    bool showHitBox;

private:
    void createWindow();
    void processEvents();
    void update(float deltaTime);
    void render();
    void handleDebugActions(sf::Event& event);

    sf::RenderWindow window;
    bool isRunning;

    Map map;
    Player player;
    Patrolling bokoblin;

    GameState currentState;
    MainMenu mainMenu;
    PauseMenu pauseMenu;
    OptionsMenu optionsMenu;
    Camera camera;
    KonamiCode konamiCode;

    sf::RectangleShape overlay;

    bool ignoreNextClick;
    bool isGamePaused;
};

#endif // GAME_HPP