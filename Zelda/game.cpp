#include "game.hpp"

Game::Game() : isRunning(false) {
    createWindow();
}

Game::~Game() {}

void Game::createWindow() {
    window.create(sf::VideoMode(), "Dungeon the Escape", sf::Style::Fullscreen);
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

}

void Game::render() {
    window.clear();

    // Draw

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