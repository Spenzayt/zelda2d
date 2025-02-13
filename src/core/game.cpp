#include "../core/game.hpp"
#include <iostream>

std::mutex mtx;

Game::Game() : isRunning(false), camera(),
player(sf::Vector2f(330, 130), 60, "assets/images/characters/link.png", 50),
zelda(sf::Vector2f(5125, 6600), 60, "assets/images/characters/zelda.png"),
sword(std::make_unique<Sword>(sf::Vector2f(943, 5020))),
mainCastleDoorKey(std::make_unique<Key>("Castle Main Door Key", "assets/images/Item/key2.png", sf::Vector2f(1430, 3390))),
    currentState(GameState::MAIN_MENU), ignoreNextClick(false), isGamePaused(false), showInventoryUI(false), bossAlreadySpawn(false),
    showHitBox(false), noclip(false), godMode(false), fullSpeed(false), musicVolume(50.f), soundVolume(50.f) {

    initEnemies();
    createWindow();
    loadAudio();
    map.importAllTextures(window);
    map.loadBackgroundFromImage();

    konamiCode.setDebugAction(sf::Keyboard::F1, [this]() {
        godMode = !godMode;
        std::cout << "Debug Action F1: godMode is now " << (godMode ? "ON" : "OFF") << std::endl;
        });
    konamiCode.setDebugAction(sf::Keyboard::F2, [this]() {
        noclip = !noclip;
        std::cout << "Debug Action F2: noclip is now " << (noclip ? "ON" : "OFF") << std::endl;
        });
    konamiCode.setDebugAction(sf::Keyboard::F3, [this]() {
        showHitBox = !showHitBox;
        std::cout << "Debug Action F3: showHitBox is now " << (showHitBox ? "ON" : "OFF") << std::endl;
        });
    konamiCode.setDebugAction(sf::Keyboard::F4, [this]() {
        fullSpeed = !fullSpeed;
        if (fullSpeed) {
            player.setSpeed(4000);
        }
        else {
            player.setSpeed(100);
        }
        std::cout << "Debug Action F4: Full Speed is now " << (fullSpeed ? "ON" : "OFF") << std::endl;
        });
}

Game::~Game() {}

void Game::loadAudio() {
    soundManager.loadMusic("menu", "assets/audio/menu_music.mp3");
    soundManager.loadMusic("game", "assets/audio/game_music.mp3");

    soundManager.loadSound("arrow", "assets/audio/arrow.wav");
}

void Game::setMusicVolume(float volume) {
    musicVolume = volume;
    soundManager.setMusicVolume(volume);
}

void Game::setSoundVolume(float volume) {
    soundVolume = volume;
    soundManager.setSoundVolume(volume);
}

void Game::initEnemies() {
    // ennemies avec mouvements pr�d�finis
    auto bokoblin1 = std::make_unique<Bokoblin>(5, sf::Vector2f(5975, 5669), 100, 5, 5); // speed, position, hp, damage, size
    bokoblin1->setPath({ { 5975,5669 }, {4420, 5669}, {3360, 5669}, {3360, 5220}, {3360, 5669} });

    auto bokoblin2 = std::make_unique<Bokoblin>(5, sf::Vector2f(2553, 3670), 100, 5, 5);
    bokoblin2->setPath({ { 2553, 3685 }, { 5272, 3685 } });

    auto bokoblin3 = std::make_unique<Bokoblin>(5, sf::Vector2f(4910, 4146), 100, 5, 5);
    bokoblin3->setPath({ { 4910, 4146 }, { 5360, 4611 }, { 5513, 4159 } });

    auto bokoblin4 = std::make_unique<Bokoblin>(5, sf::Vector2f(3690, 1131), 100, 5, 5);
    bokoblin4->setPath({ { 3690, 1131 }, { 3718, 1552 }, { 3939, 1552 }, { 3939, 2184 },{ 3939, 1552 }, { 3718, 1552 } });

    auto bokoblin5 = std::make_unique<Bokoblin>(5, sf::Vector2f(4674, 2133), 100, 5, 5);
    bokoblin5->setPath({{4674, 2133}, {4269, 2133}, {4269, 1302}, {4269, 2133}, {4269, 1302}, {4269, 2133} });

    auto bokoblin6 = std::make_unique<Bokoblin>(5, sf::Vector2f(3588, 9359), 100, 5, 5);
    bokoblin6->setPath({ {3588, 9359}, {4220, 9359 }, {4269, 8862}, {3583, 8862}, {4269, 8862}, {4220, 9359} });
    
    auto bokoblin7 = std::make_unique<Bokoblin>(5, sf::Vector2f(510, 9485), 100, 5, 5);
    bokoblin7->setPath({ {510, 9485}, {510, 8583 }, {510, 9485}});

    ennemies.push_back(std::move(bokoblin1));
    ennemies.push_back(std::move(bokoblin2));
    ennemies.push_back(std::move(bokoblin3));
    ennemies.push_back(std::move(bokoblin4));
    ennemies.push_back(std::move(bokoblin5));
    ennemies.push_back(std::move(bokoblin6));
    ennemies.push_back(std::move(bokoblin7));

    // ennemies qui suit le joueur
    ennemies.push_back(std::make_unique<Chaser>(4, sf::Vector2f(5819, 3868), 100, 5, 5, player));
    ennemies.push_back(std::make_unique<Chaser>(4, sf::Vector2f(2352, 4409), 100, 5, 5, player));

    // archers
    ennemies.push_back(std::make_unique<Archer>(0, sf::Vector2f(3793, 2665), 100, 10, 5, player, soundManager));
    ennemies.push_back(std::make_unique<Archer>(0, sf::Vector2f(4359, 2665), 100, 10, 5, player, soundManager));
    ennemies.push_back(std::make_unique<Archer>(0, sf::Vector2f(796, 8935), 100, 10, 5, player, soundManager));
    ennemies.push_back(std::make_unique<Archer>(0, sf::Vector2f(4382, 8473), 100, 10, 5, player, soundManager));
    ennemies.push_back(std::make_unique<Archer>(0, sf::Vector2f(1158, 2811), 100, 10, 5, player, soundManager));
    ennemies.push_back(std::make_unique<Archer>(0, sf::Vector2f(930, 2811), 100, 10, 5, player, soundManager));
    ennemies.push_back(std::make_unique<Archer>(0, sf::Vector2f(679, 2811), 100, 10, 5, player, soundManager));
   
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
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && currentState == GameState::PLAYING) {
            currentState = GameState::PAUSE;
            isGamePaused = true;
        }
        if (konamiCode.isActivated(event)) {
        }
        if (konamiCode.isKonamiActivated()) {
            konamiCode.handleDebugActions(event);
        }
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::I) {
            showInventoryUI = !showInventoryUI;
        }
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right) {
            player.attack(ennemies);
        }
        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                map.handleMouseClick(mousePos);
            }
        }


    }
    handleGameState(event);
}

void Game::checkCollisionsPlayerEnemies() {
    for (const auto& enemy : ennemies) {
        if (player.getGlobalBounds().intersects(enemy->getGlobalBounds()) && !godMode) {
            player.damage(enemy->getDamage());
            checkIfPlayerIsDead();
        }
    }
   /* if (bossAlreadySpawn) {
        if (player.getGlobalBounds().intersects(boss->getGlobalBounds()) && !godMode) {
            player.damage(boss->getDamage());
            checkIfPlayerIsDead();
        }
    }*/
}

void Game::checkIfPlayerIsDead() {
    if (player.isDead()) {
        currentState = GameState::GAMEOVER;
    }
}

bool Game::getGodMode() const {
    return godMode;
}

void Game::updateMap(float deltaTime, const sf::FloatRect& playerHitbox) {
    std::lock_guard<std::mutex> lock(mtx);
    map.update(deltaTime, playerHitbox);
}

void Game::updatePlayer(float deltaTime, const std::vector<sf::Sprite>& bushes) {
    std::lock_guard<std::mutex> lock(mtx);
    player.update(deltaTime, bushes);
}

void Game::updateEnemies(float deltaTime) {
    std::lock_guard<std::mutex> lock(mtx);
    for (auto& enemy : ennemies) {
        enemy->update(deltaTime, map.getBushes());
    }
}

void Game::update(float deltaTime) {
    soundManager.setMusicVolume(optionsMenu.getMusicLevel());
    soundManager.setSoundVolume(optionsMenu.getSoundLevel());

    if (currentState == GameState::PLAYING) {
        if (!bossAlreadySpawn) {
            if (map.areAllTorchesOn()) {
                auto boss1 = std::make_unique<Boss>(2, sf::Vector2f(2355, 9245), 100, 15, 5, player);
                boss1->setPath({ {2355, 9245}, {1835, 9245 }, {1835, 8933} , {2355, 8933} });
                ennemies.push_back(std::move(boss1));
                bossAlreadySpawn = true;
            }
        }

        sf::FloatRect playerHitbox = player.getHitbox();
        std::vector<sf::Sprite> bushes = map.getBushes();

        std::thread mapThread(&Game::updateMap, this, deltaTime, playerHitbox);
        std::thread playerThread(&Game::updatePlayer, this, deltaTime, std::ref(bushes));
        std::thread enemiesThread(&Game::updateEnemies, this, deltaTime);

        mapThread.join();
        playerThread.join();
        enemiesThread.join();

        checkIfPlayerIsDead();
        checkCollisionsPlayerEnemies();

        if (!noclip) {
            player.update(deltaTime, bushes);
        }
        else {
            player.setPosition(player.getPosition() + player.getMovementDelta(deltaTime));
        }
        player.checkDoor(map.doors);

        if (player.getGlobalBounds().intersects(zelda.getGlobalBounds())) {
            currentState = GameState::VICTORY;
        }

        const Map::Zone* currentZone = map.getZoneContaining(player.getPosition());
        if (currentZone != nullptr) {
            if (currentZone->getName() == "Spawn House"
                || currentZone->getName() == "Tunnel 1" || currentZone->getName() == "Tunnel 2"
                || currentZone->getName() == "Castle Right" || currentZone->getName() == "Castle End Room") {
                camera.update(player.getPosition(), deltaTime, false, false, currentZone->bounds, 1.4f);
            }
            else if (currentZone->getName() == "Castle Left") {
                camera.update(player.getPosition(), deltaTime, false, false, currentZone->bounds, 1.9f);
            }
            else if (currentZone->getName() == "Castle Middle") {
                camera.update(player.getPosition(), deltaTime, false, false, currentZone->bounds, 1.f);
            }
            else {
                camera.update(player.getPosition(), deltaTime, false, false, currentZone->bounds);
            }
        }
        else {
            camera.resetToDefault();
            camera.update(player.getPosition(), deltaTime, false, true);
        }
        if (sword && player.getHitbox().intersects(sword->getBounds())) {
            player.addItemToInventory(*sword);
            sword.reset();
        }
        if (mainCastleDoorKey && player.getHitbox().intersects(mainCastleDoorKey->getBounds())) {
            player.addItemToInventory(*mainCastleDoorKey);
            mainCastleDoorKey.reset();
        }
    }
    else {
        camera.resetToDefault();
        camera.update(player.getPosition(), deltaTime, true, true);
    }
}

void Game::drawEnemies() {
    for (auto& enemy : ennemies) {
        enemy->draw(window);
    }
}

void Game::render() {
    window.clear(sf::Color(67, 53, 52));

    if (currentState == GameState::MAIN_MENU) {
        mainMenu.render(window);
    }
    if (currentState == GameState::PLAYING) {
        map.draw(window);
        camera.applyView(window);

        if (showHitBox) {
            map.drawMapHitBox(window);
        }
        if (mainCastleDoorKey) {
            mainCastleDoorKey->draw(window);
        }
        if (sword) {
            sword->draw(window);
        }

        zelda.draw(window);
        player.draw(window);
        drawEnemies();

        if (showHitBox) { 
            player.drawHitBox(window);
        }
        if (showInventoryUI) {
            drawInventory(window);
        }
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
    if (currentState == GameState::GAMEOVER) {
        map.draw(window);
        camera.applyView(window);
        player.draw(window);
        drawPauseMenu();
        gameOver.draw(window);
    }
    if (currentState == GameState::VICTORY) {
        map.draw(window);
        camera.applyView(window);
        player.draw(window);
        drawPauseMenu();
        win.draw(window);
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


void Game::drawInventory(sf::RenderWindow& window) {
    sf::RectangleShape inventoryBackground(sf::Vector2f(400, 300)); // Taille de l'inventaire
    inventoryBackground.setFillColor(sf::Color(0, 0, 0, 200)); // Fond semi-transparent
    inventoryBackground.setPosition(window.getView().getCenter().x - 200, window.getView().getCenter().y - 150);


    window.draw(inventoryBackground);

    sf::Font font;
    if (!font.loadFromFile("assets/fonts/arial.ttf")) {
        std::cout << "Erreur chargement de la police\n";
        return;
    }
    sf::Text inventoryText;
    inventoryText.setFont(font);
    inventoryText.setCharacterSize(20);
    inventoryText.setFillColor(sf::Color::White);

    float offsetY = 10;
    for (const auto& item : player.getInventory().getItems()) {
        inventoryText.setString("- " + item.getName() + " (Valeur: " + std::to_string(item.getValue()) + ")");
        inventoryText.setPosition(window.getView().getCenter().x - 190, window.getView().getCenter().y - 140 + offsetY);
        offsetY += 30;
        window.draw(inventoryText);
    }
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

void Game::handleGameState(sf::Event& event) {
    static std::string currentMusicState = "";
    static bool isMusicPaused = false;

    if (ignoreNextClick) {
        if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
            ignoreNextClick = false;
        }
        return;
    }
    if (currentState == GameState::MAIN_MENU) {
        if (currentMusicState != "menu") {
            soundManager.stopMusic();
            soundManager.playMusic("menu", true);
            currentMusicState = "menu";
            isMusicPaused = false;
        }

        mainMenu.handleMouseHover(window);
        int action = mainMenu.handleInput(window, event);

        switch (action) {
        case 0:
            resetGame();
            currentState = GameState::PLAYING;
            ignoreNextClick = true;
            break;
        case 1:
            currentState = GameState::OPTIONS;
            break;
        case 2:
            isRunning = false;
            break;
        }
    }
    if (currentState == GameState::PLAYING) {
        if (currentMusicState != "game") {
            if (!isMusicPaused) {
                soundManager.stopMusic();
                soundManager.playMusic("game", true);
                currentMusicState = "game";
            }
            isMusicPaused = false;
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
        if (currentMusicState != "pause") {
            soundManager.stopMusic();
            soundManager.playMusic("menu", true);
            currentMusicState = "pause";
        }
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
    if (currentState == GameState::GAMEOVER) {
        gameOver.handleMouseHover(window);
        int action = gameOver.handleInput(window, event);
        switch (action) {
        case 0:
            resetPlayer();
            currentState = GameState::PLAYING;
            isGamePaused = false;
            break;
        case 1:
            resetGame();
            break;
        case 2:
            currentState = GameState::MAIN_MENU;
            ignoreNextClick = true;
            break;
        }
    }
    if (currentState == GameState::VICTORY) {
        win.handleMouseHover(window);
        int action = win.handleInput(window, event);
        switch (action) {
        case 0:
            resetGame();
            break;
        case 1:
            currentState = GameState::MAIN_MENU;
            ignoreNextClick = true;
            break;
        }
    }
}

void Game::resetGame() {
    player.setPosition(sf::Vector2f(330, 130));
    player.reset();
    ennemies.clear();
    initEnemies();

    currentState = GameState::PLAYING;
    isGamePaused = false;
}

void Game::resetPlayer() {
    bossAlreadySpawn = false;
    player.reset();
    ennemies.clear();
    initEnemies();
}