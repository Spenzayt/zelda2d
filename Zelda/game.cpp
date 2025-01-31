#include "game.hpp"

Game::Game() : isRunning(false), player(sf::Vector2f(100, 100), 100, "assets/characters/Link.png"), 
currentState(GameState::MAIN_MENU), ignoreNextClick(false), isGamePaused(false) {
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
        if (event.type == sf::Event::Closed || Keyboard::isKeyPressed(Keyboard::P)) {
            isRunning = false;
        }
    }
    if (Keyboard::isKeyPressed(Keyboard::Escape) && currentState == GameState::PLAYING) {
        currentState = GameState::PAUSE;
        isGamePaused = true;
    }
    handleGameState(event);
}

void Game::update(float deltaTime) {
    if (currentState == GameState::PLAYING) {
        map.update(deltaTime);
        player.update(deltaTime);
    }
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
    if (currentState == GameState::OPTIONS) {
        if (isGamePaused) {
            map.draw(window);
            player.draw(window);
            drawPauseMenu();
        }
        optionsMenu.render(window);
    }
    if (currentState == GameState::PAUSE) {
        map.draw(window);
        player.draw(window);
        drawPauseMenu();
        pauseMenu.render(window);
    }
    window.display();
}

void Game::drawPauseMenu()
{
    overlay.setSize(Vector2f(1920, 1080));
    overlay.setFillColor(Color(0, 0, 0, 150));
    window.draw(overlay);
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
    if (ignoreNextClick) {
        if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
            ignoreNextClick = false; 
        }
        return;
    }
    if (currentState == GameState::MAIN_MENU) {
        mainMenu.handleMouseHover(window);
        int action = mainMenu.handleInput(window, event);

        switch (action) {
        case 0:
            currentState = GameState::PLAYING;
            break;
        case 1:
            currentState = GameState::OPTIONS;
            break;
        case 2:
            isRunning = false;
            break;
        }
    }
    if (currentState == GameState::OPTIONS) {
        optionsMenu.handleMouseHover(window);
        int action = optionsMenu.handleInput(window, event);

        if (action == 2) {
            if (isGamePaused) {
                currentState = GameState::PLAYING;
                ignoreNextClick = true;
            }
            else {
                currentState = GameState::MAIN_MENU;
                ignoreNextClick = true;
            }
        }
    }
    if (currentState == GameState::PAUSE) {
        pauseMenu.handleMouseHover(window);
        int action = pauseMenu.handleInput(window, event);

        switch (action) {
        case 0:
            currentState = GameState::PLAYING;
            isGamePaused = false;
            break;
        case 1:
            currentState = GameState::OPTIONS;
            break;
        case 2:
            currentState = GameState::MAIN_MENU;
            isGamePaused = false;
            ignoreNextClick = true;
            break;
        }
    }
}
