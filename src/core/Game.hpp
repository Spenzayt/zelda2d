#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include "../map/Map.hpp"
#include "../entities/Player.hpp"
#include "../entities/Bokoblin.hpp"
#include "../entities/Chaser.hpp"
#include "../entities/Archer.hpp"
#include "../ui/Menu.hpp"
#include "../ui/MainMenu.hpp"
#include "../ui/PauseMenu.hpp"
#include "../ui/OptionsMenu.hpp"
#include "../systems/camera.hpp"
#include "../systems/KonamiCode.hpp"
#include "../objet/MasterSword.hpp"
#include "../objet/Key.hpp"
#include <vector>
#include <memory>

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
    void updateEnemies(float deltaTime);
    void drawEnemies();
    void drawPauseMenu();

    bool godMode;
    bool noclip;
    bool showHitBox;
    bool fullSpeed;

private:
    void initEnemies();
    void createWindow();
    void processEvents();
    void update(float deltaTime);
    void render();
    void drawInventory(sf::RenderWindow& window);

    sf::RenderWindow window;
    bool isRunning;

    Map map;
    Player player;

    
    std::vector<std::unique_ptr<Enemy>> ennemies;
    std::unique_ptr<Sword> sword;
    std::unique_ptr<Key> mainCastleDoorKey;

    GameState currentState;
    MainMenu mainMenu;
    PauseMenu pauseMenu;
    OptionsMenu optionsMenu;
    Camera camera;
    KonamiCode konamiCode;

    sf::RectangleShape overlay;

    bool ignoreNextClick;
    bool isGamePaused;
    bool showInventoryUI;
};

#endif // GAME_HPP