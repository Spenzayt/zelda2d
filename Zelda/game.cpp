#include "game.hpp"

Game::Game() : isRunning(false), player(sf::Vector2f(100, 100), 100, "assets/characters/Link.png"), currentState(GameState::MAIN_MENU) {
    createWindow();
    map.importAllTextures();
    map.loadBackgroundFromImage();
}

Game::~Game() {}

void Game::createWindow() {
    window.create(sf::VideoMode(), "Zelda", sf::Style::Fullscreen);
    window.setFramerateLimit(60);
    isRunning = true;
}

void Game::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape)) {
            isRunning = false;
        }
    }
    handleGameState(event);
}

void Game::update(float deltaTime) {
    map.update(deltaTime);
    player.update(deltaTime);
}

void Game::render() {
    window.clear();
    if (currentState == GameState::MAIN_MENU) {
        mainMenu.render(window);
    }
    if (currentState == GameState::PLAYING) {
        map.draw(window);
        player.draw(window);
    }
   
    window.display();
}

void Game::run() {
    sf::Clock clock;

    while (isRunning) {
        processEvents();
        float deltaTime = clock.restart().asSeconds();
        update(deltaTime);
        render();
        mainMenu.handleMouseHover(window);
    }
}

void Game::handleGameState(Event& event)
{
    mainMenu.handleMouseHover(window);
    int action = mainMenu.handleInput(window, event);

    switch (action) {
    case 0: 
        currentState = GameState::PLAYING;
        break;
    case 2:
        isRunning = false;
        break;
    }
}
