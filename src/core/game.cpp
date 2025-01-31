#include "../core/game.hpp"

Game::Game() 
    : isRunning(false), 
      player(sf::Vector2f(4850, 5200), 60, "assets/images/characters/Link.png"),
    bokoblin(sf::Vector2f(300, 300), 50, { sf::Vector2f(1000, 300), sf::Vector2f(500, 500), sf::Vector2f(800, 700),sf::Vector2f(100, 600) }, "assets/images/characters/Bokoblin.png")
{
    createWindow();
    map.importAllTextures(window);
    map.loadBackgroundFromImage();
}

Game::~Game() {}

void Game::createWindow() {
    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    window.create(desktopMode, "Zelda", sf::Style::Fullscreen);
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