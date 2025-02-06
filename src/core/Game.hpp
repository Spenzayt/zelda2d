#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "../map/Map.hpp"
#include "../entities/Player.hpp"
#include "../entities/Bokoblin.hpp"
#include "../entities/Chaser.hpp"
#include "../entities/Archer.hpp"
#include "../entities/Zelda.hpp"
#include "../ui/Menu.hpp"
#include "../ui/MainMenu.hpp"
#include "../ui/PauseMenu.hpp"
#include "../ui/OptionsMenu.hpp"
#include "../ui/Renderer.hpp"
#include "../ui/GameOver.hpp"
#include "../ui/Win.hpp"
#include "../systems/camera.hpp"
#include "../systems/KonamiCode.hpp"
#include "../systems/SoundManager.hpp"
#include "../entities/Boss.hpp"
#include "../objet/MasterSword.hpp"
#include "../objet/Key.hpp"
#include <vector>
#include <memory>
#include <mutex>
#include <thread>

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
        OPTIONS,
    };

    void run();
    void handleGameState(sf::Event& event);
    void updateEnemies(float deltaTime);
    void updatePlayer(float deltaTime, const std::vector<sf::Sprite>& bushes);
    void updateMap(float deltaTime, const sf::FloatRect& playerHitbox);
    void drawEnemies();
    void drawPauseMenu();

    void checkCollisionsPlayerEnemies();
    void checkIfPlayerIsDead();
    bool getGodMode() const;
    bool godMode;
    bool noclip;
    bool showHitBox;
    bool fullSpeed;

    void loadAudio();
    void setMusicVolume(float volume);
    void setSoundVolume(float volume);
private:
    void initEnemies();
    void createWindow();
    void processEvents();
    void update(float deltaTime);
    void render();
    void drawInventory(sf::RenderWindow& window);

    void resetGame();
    void resetPlayer();
    sf::RenderWindow window;
    bool isRunning;

    Map map;
    Player player;
    Zelda zelda;
    Boss* boss;

    std::vector<std::unique_ptr<Enemy>> ennemies;
    //Player::PlayerLocation playerLocation;

    std::unique_ptr<Sword> sword;
    std::unique_ptr<Key> mainCastleDoorKey;

    GameState currentState;
    MainMenu mainMenu;
    PauseMenu pauseMenu;
    OptionsMenu optionsMenu;

    GameOver gameOver;
    Win win;

    Camera camera;
    KonamiCode konamiCode;
    SoundManager soundManager;

    sf::RectangleShape overlay;

    sf::Music backgroundMusic;
    std::vector<sf::Sound> soundEffects;
    sf::SoundBuffer soundBuffer;


    float musicVolume;
    float soundVolume;

    bool ignoreNextClick;
    bool isGamePaused;
    bool showInventoryUI;

    bool bossAlreadySpawn;
};

#endif // GAME_HPP