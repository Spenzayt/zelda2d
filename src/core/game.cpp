#include "../core/game.hpp"
#include <iostream>

Game::Game() : isRunning(false), camera(),
    player(sf::Vector2f(4850, 5200), 60, "assets/images/characters/Link.png"), 
    currentState(GameState::MAIN_MENU), ignoreNextClick(false), isGamePaused(false) {
    
    initEnemies();
    createWindow();
    map.importAllTextures(window);
    map.loadBackgroundFromImage();
}

Game::~Game() {}

void Game::initEnemies()
{
    ennemies.push_back(std::make_unique<Bokoblin>(5, sf::Vector2f(4850, 5200), 100, 10, 5));
}

void Game::createWindow() {
    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    window.create(desktopMode, "Zelda", sf::Style::Fullscreen);
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);
    isRunning = true;
}

void Game::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
            isRunning = false;
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && currentState == GameState::PLAYING) {
        currentState = GameState::PAUSE;
        isGamePaused = true;
    }
    handleGameState(event);
}

void Game::update(float deltaTime) {
    if (currentState == GameState::PLAYING) {
        map.update(deltaTime);
        player.update(deltaTime, map.getBushes());
        bokoblin.update(deltaTime, map.getBushes());

        const Map::Zone* currentZone = map.getZoneContaining(player.getPosition());
        if (currentZone) {
            camera.update(player.getPosition(), deltaTime, false, false, currentZone->bounds);
        }
        else {
            camera.resetToDefault();
            camera.update(player.getPosition(), deltaTime, false, true);
        }
    }
    else {
        camera.resetToDefault();
        camera.update(player.getPosition(), deltaTime, true, true);
    }
}

void Game::render() {
    window.clear();
    if (currentState == GameState::MAIN_MENU) {
        mainMenu.render(window);
    }
    if (currentState == GameState::PLAYING) {
        map.draw(window);
        camera.applyView(window);
        player.draw(window);
        bokoblin.draw(window);
    }
    if (currentState == GameState::OPTIONS) {
        if (isGamePaused) {
            map.draw(window);
            camera.applyView(window);
            player.draw(window);
            drawPauseMenu();
        }
        optionsMenu.render(window);
    }
    if (currentState == GameState::PAUSE) {
        map.draw(window);
        camera.applyView(window);
        player.draw(window);
        drawPauseMenu();
        pauseMenu.render(window);
    }
    window.display();
}

void Game::drawPauseMenu() {
    sf::Vector2f viewCenter = window.getView().getCenter();
    overlay.setPosition(viewCenter.x - overlay.getSize().x / 2, viewCenter.y - overlay.getSize().y / 2);

    overlay.setSize(sf::Vector2f(Config::WINDOW_WIDTH, Config::WINDOW_HEIGHT));
    overlay.setFillColor(sf::Color(0, 0, 0));
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

void Game::handleGameState(sf::Event& event)
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
            ignoreNextClick = true;
            break;
        case 1:
            currentState = GameState::OPTIONS;
            ignoreNextClick = true;
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
            ignoreNextClick = true;
            break;
        case 2:
            currentState = GameState::MAIN_MENU;
            isGamePaused = false;
            ignoreNextClick = true;
            break;
        }
    }
}