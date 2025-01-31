#include "game.hpp"

Game::Game() 
    : isRunning(false), 
      player(sf::Vector2f(100, 50), 100, "assets/characters/Link.png"),
    bokoblin(sf::Vector2f(300, 300), 50, { sf::Vector2f(1000, 300), sf::Vector2f(500, 500), sf::Vector2f(800, 700),sf::Vector2f(100, 600) }, "assets\\characters\\Bokoblin.png")
{
    createWindow();
    map.importAllTextures();
    map.loadBackgroundFromImage();
}

Game::~Game() {}

void Game::createWindow() {
    window.create(sf::VideoMode(), "Zelda", sf::Style::Fullscreen);
    window.setFramerateLimit(1000);
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
    map.update(deltaTime, player.getPosition());
    player.update(deltaTime, map.getTrees(), map.getBushes());
    bokoblin.update(deltaTime, map.getTrees(), map.getBushes());
}


void Game::render() {
    window.clear();

    map.draw(window);
    player.draw(window);
    bokoblin.draw(window);

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