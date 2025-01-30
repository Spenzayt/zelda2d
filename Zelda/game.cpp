#include "game.hpp"

Game::Game() : isRunning(false), player(sf::Vector2f(100, 100), 100, "assets/characters/Link.png") {
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
        if (event.type == sf::Event::Closed) {
            isRunning = false;
        }
    }
}

void Game::update(float deltaTime) {
    map.update(deltaTime);
    player.update(deltaTime);
}

void Game::render() {
    window.clear();

    map.draw(window);
    player.draw(window);

    window.display();
}

void Game::run() {
    sf::Clock clock;

    while (isRunning) {
        processEvents();
        float deltaTime = clock.restart().asSeconds();
        update(deltaTime);
        render();
    }
}