#include "Player.hpp"
#include <iostream>


Player::Player(sf::Vector2f spawnposition, float size, const std::string& texturePath, float hp) : hasKey(false)
{
    position = spawnposition;
    previousPosition = position;

    maxHp = 5;
    heal = hp;

   // damage = 10;
    speed = 100;

    if (!texture.loadFromFile(texturePath)) {
        std::cerr << "Error loading texture from: " << texturePath << std::endl;
    }

    player.setTexture(texture);
    player.setScale(size / static_cast<float>(texture.getSize().x), size / static_cast<float>(texture.getSize().y));
    sf::FloatRect bounds = player.getLocalBounds();
    player.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);
    player.setPosition(position);

    hitbox = sf::FloatRect(
        position.x - size / 2,
        position.y - size / 2,
        size,
        size
    );

    physics.loadCollisionImage();
    physics.resizeCollisionImage(1539*4, 2543*4);
}

void Player::update(float deltatime, const std::vector<sf::Sprite>& bushes) {
    previousPosition = position;
    handleInput(deltatime);

    sf::Vector2f newPosition = position + getMovementDelta(deltatime);
    hitbox.left = newPosition.x;
    hitbox.top = newPosition.y;

    if (physics.isCollidingWithMap(getHitbox())) {
        position = previousPosition;
    }
    else {
        position = newPosition;
        player.setPosition(position);
        checkCollisionWithMap(bushes);
    }
}

void Player::handleInput(float deltatime) {
    previousPosition = position;

    sf::Vector2f movement = InputHandler::getMovementDirection();
    position.x += movement.x * speed * deltatime;
    position.y += movement.y * speed * deltatime;
}

void Player::setSpeed(float amount) {
    speed = amount;
}

void Player::draw(sf::RenderWindow& window) {
    window.draw(player);

    static sf::Font font;
    if (!font.loadFromFile("assets/fonts/arial.ttf")) {
        std::cerr << "Error loading font!" << std::endl;
        return;
    }

    sf::Text text;
    text.setFont(font);
    text.setString("Player Position: (" + std::to_string(static_cast<int>(position.x)) + ", " + std::to_string(static_cast<int>(position.y)) + ")");
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);

    sf::View currentView = window.getView();
    sf::FloatRect viewBounds(
        currentView.getCenter().x - currentView.getSize().x / 2.f,
        currentView.getCenter().y - currentView.getSize().y / 2.f,
        currentView.getSize().x,
        currentView.getSize().y
    );

    text.setPosition(viewBounds.left + 10.f, viewBounds.top + 10.f);

    window.draw(text);
}

void Player::drawHitBox(sf::RenderWindow& window) {
    sf::FloatRect hitbox = getHitbox();
    sf::RectangleShape hitboxShape(sf::Vector2f(hitbox.width, hitbox.height));
    hitboxShape.setPosition(hitbox.left, hitbox.top);
    hitboxShape.setFillColor(sf::Color::Transparent);
    hitboxShape.setOutlineColor(sf::Color::Blue);
    hitboxShape.setOutlineThickness(2.f);
    window.draw(hitboxShape);
}

void Player::checkCollisionWithWalls(const std::vector<sf::RectangleShape>& walls) {
    sf::Vector2f newPosition;
    if (Physics::checkCollision(player, walls, newPosition)) {
        position = previousPosition;
        player.setPosition(position);
    }
}

void Player::checkCollisionWithMap(const std::vector<sf::Sprite>& bushes) {
    for (const auto& bush : bushes) {
        if (getHitbox().intersects(bush.getGlobalBounds())) {
            position = previousPosition;
            player.setPosition(position);
            return;
        }
    }
}

void Player::reset()
{
    heal = maxHp;
    player.setPosition(sf::Vector2f(4850, 5200));
}

void Player::damage(int damages)
{
    heal -= damages;
    if (heal < 0) {
        heal = 0;
    }
}

sf::Vector2f Player::getPosition() const {
    return player.getPosition();
}

float Player::getHealth() const
{
    return heal;
}

float Player::getSpeed() const
{
    return speed;
}

bool Player::isDead() const
{
    return heal <= 0;
}

void Player::setPosition(const sf::Vector2f& position) {
    this->position = position;
    player.setPosition(position);
}

sf::Vector2f Player::getMovementDelta(float deltatime) const {
    sf::Vector2f movement = InputHandler::getMovementDirection();
    sf::Vector2f movementDelta(movement.x * speed * deltatime, movement.y * speed * deltatime);
    return movementDelta;
}

sf::FloatRect Player::getHitbox() const {
    sf::FloatRect bounds = player.getGlobalBounds();

    bounds.left = position.x - bounds.width / 2;
    bounds.top = position.y - bounds.height / 2;

    bounds.left += bounds.width * 0.2f;
    bounds.top += bounds.height * 0.2f;
    bounds.width *= 0.6f;
    bounds.height *= 0.6f;

    return bounds;
}

void Player::checkDoor(const std::vector<Map::Door>& doors) {
    for (const auto& door : doors) {
        if (getHitbox().intersects(door.bounds)) {
            if (door.name.find("Entry House") != std::string::npos) {
                std::cout << "test" << std::endl;
                setPosition(sf::Vector2f(450, 590));
                break;
            }
            else if (door.name.find("Exit House") != std::string::npos) {
                setPosition(sf::Vector2f(4880, 5230));
                break;
            }
            else if (door.name.find("Entry Castle Door 1") != std::string::npos) {
                setPosition(sf::Vector2f(750, 9240));
                break;
            }
            else if (door.name.find("Exit Castle Door 1") != std::string::npos) {
                setPosition(sf::Vector2f(1300, 9240));
                break;
            }
            else if (door.name.find("Entry Castle Door 2") != std::string::npos) {
                setPosition(sf::Vector2f(850, 8730));
                break;
            }
            else if (door.name.find("Exit Castle Door 2") != std::string::npos) {
                setPosition(sf::Vector2f(1200, 8730));
                break;
            }
            else if (door.name.find("Entry Castle Door 3") != std::string::npos) {
                setPosition(sf::Vector2f(3350, 9240));
                break;
            }
            else if (door.name.find("Exit Castle Door 3") != std::string::npos) {
                setPosition(sf::Vector2f(2800, 9240));
                break;
            }
            else if (door.name.find("Entry Castle Door 4") != std::string::npos) {
                setPosition(sf::Vector2f(5130, 7900));
                break;
            }
            else if (door.name.find("Exit Castle Door 4") != std::string::npos) {
                setPosition(sf::Vector2f(2040, 8430));
                break;
            }
            else if (door.name.find("Entry Castle Door 5") != std::string::npos) {
                setPosition(sf::Vector2f(3280, 300));
                break;
            }
            else if (door.name.find("Exit Castle Door 5") != std::string::npos) {
                setPosition(sf::Vector2f(510, 10030));
                break;
            }
            else if (door.name.find("Entry Castle Door 6") != std::string::npos) {
                setPosition(sf::Vector2f(2045, 9910));
                break;
            }
            else if (door.name.find("Exit Castle Door 6") != std::string::npos) {
                setPosition(sf::Vector2f(4100, 1130));
                break;
            }
            else if (door.name.find("Entry Castle Door 7") != std::string::npos) {
                setPosition(sf::Vector2f(4940, 300));
                break;
            }
            else if (door.name.find("Exit Castle Door 7") != std::string::npos) {
                setPosition(sf::Vector2f(3580, 10030));
                break;
            }
            else if (door.name.find("Entry Tunnel 1") != std::string::npos) {
                setPosition(sf::Vector2f(1530, 2700));
                break;
            }
            else if (door.name.find("Entry Tunnel 2") != std::string::npos) {
                setPosition(sf::Vector2f(380, 3320));
                break;
            }
            else if (door.name.find("Exit Tunnel 2") != std::string::npos) {
                setPosition(sf::Vector2f(380, 2710));
                break;
            }
            else if (door.name.find("Entry Tunnel 3") != std::string::npos) {
                setPosition(sf::Vector2f(4940, 970));
                break;
            }
            else if (door.name.find("Exit Tunnel 3") != std::string::npos) {
                setPosition(sf::Vector2f(380, 3800));
                break;
            }
            else if (door.name.find("Entry Castle Main Door") != std::string::npos) {
                if (hasItemInInventory("Castle Main Door Key")) {
                    setPosition(sf::Vector2f(4100, 2330));
                }
                else {
                    std::cout << "You need the Castle Main Door Key to enter." << std::endl;
                }
                break;
            }
            else if (door.name.find("Exit Castle Main Door") != std::string::npos) {
                if (hasItemInInventory("Castle Main Door Key")) {
                    setPosition(sf::Vector2f(4100, 2670));
                }
                else {
                    std::cout << "You need the Castle Main Door Key to enter." << std::endl;
                }
                break;
            }
        }
    }
}