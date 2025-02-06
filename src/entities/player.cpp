#include "Player.hpp"
#include <iostream>


Player::Player(sf::Vector2f spawnposition, float size, const std::string& texturePath, float hp) {
    position = spawnposition;
    previousPosition = position;

    maxHp = 50;
    heal = hp;
    speed = 100;
    damageCooldown = 1.0f;


    if (!texture.loadFromFile(texturePath)) {
        std::cerr << "Error loading texture from: " << texturePath << std::endl;
    }

    initHeartTexture();
    initLifeTexture();

    for (int i = 0; i < maxHp / 10; i++) {
        sf::Sprite heart(fullHeartTexture);
        hearts.push_back(heart);
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

    if (damageCooldown > 0) {
        damageCooldown -= deltatime;
    }
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

    float heartSpacing = 40.f;
    float marginTop = 55.f;
    float marginRight = 10.f;

    sf::View view = window.getView();
    sf::Vector2f viewSize = view.getSize();
    sf::Vector2f viewCenter = view.getCenter();

    float zoomFactor = viewSize.x / window.getDefaultView().getSize().x;

    float x = viewCenter.x + (viewSize.x / 2) - marginRight - (maxHp / 10) * heartSpacing * zoomFactor;

        for (int i = 0; i < maxHp / 10; i++) {
            hearts[i].setScale(zoomFactor, zoomFactor);
            hearts[i].setPosition(x + i * heartSpacing * zoomFactor, viewCenter.y - (viewSize.y / 2) + marginTop * zoomFactor) ;

            if (heal >= (i + 1) * 10) {
                hearts[i].setTexture(fullHeartTexture);
            }
            else if (heal >= i * 10 + 5) {
                hearts[i].setTexture(halfHeartTexture);
             }
            else {
                hearts[i].setTexture(emptyHeartTexture);
            }

            window.draw(hearts[i]);
        }
    
    sf::Text text;
    text.setFont(font);
    text.setString("Player Position: (" + std::to_string(static_cast<int>(position.x)) + ", " + std::to_string(static_cast<int>(position.y)) + ")");
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);

    sf::FloatRect viewBounds(
        viewCenter.x - viewSize.x / 2.f,
        viewCenter.y - viewSize.y / 2.f,
        viewSize.x,
        viewSize.y
    );

    text.setPosition(viewBounds.left + 10.f * zoomFactor, viewBounds.top + 10.f * zoomFactor);

    window.draw(text);

    life.setTexture(textureLife);
    life.setScale(zoomFactor, zoomFactor);
    float xLife = viewCenter.x + (viewSize.x / 2);
    life.setPosition(viewBounds.left + 1697 * zoomFactor, viewBounds.top + 5.f * zoomFactor);
    window.draw(life);
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

void Player::initHeartTexture()
{
    if (!fullHeartTexture.loadFromFile("assets/images/interface/fullheart.png") ||
        !halfHeartTexture.loadFromFile("assets/images/interface/halfheart.png") || 
    !emptyHeartTexture.loadFromFile("assets/images/interface/emptyheart.png")) {
        std::cerr << "Error loading the heart textures !" << std::endl;
    }
}

void Player::initLifeTexture()
{
    if (!textureLife.loadFromFile("assets/images/interface/life.png")) {
        std::cerr << "Error loading life texture !" << std::endl;
    }
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
}

void Player::damage(int damages)
{
    if (damageCooldown <= 0) {
        heal -= damages;
        if (heal < 0) {
            heal = 0;
        }
    }
    
    damageCooldown = 1.0f;
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

sf::FloatRect Player::getGlobalBounds() const
{
    return player.getGlobalBounds();
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
                if (hasItemInInventory("Boss Key")) {
                    setPosition(sf::Vector2f(5130, 7900));
                }
                else {
                    std::cout << "You need the Boss Key to enter." << std::endl;
                }
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
void Player::attack(std::vector<std::unique_ptr<Enemy>>& enemies) {
    if (!hasSword()) return;

    float attackRange = 50.0f;

    // Supprime les ennemis morts apr�s l'attaque
    enemies.erase(
        std::remove_if(enemies.begin(), enemies.end(),
            [this, attackRange](std::unique_ptr<Enemy>& enemy) {
                float distance = std::hypot(enemy->getPosition().x - position.x,
                    enemy->getPosition().y - position.y);
                if (distance < attackRange) {
                    enemy->takeDamage(10);
                    std::cout << "Enemy hit!" << std::endl;
                }
                return enemy->isDead(); // Supprime si l'ennemi est mort
            }),
        enemies.end());
}

bool Player::hasSword() const {
    
    return true;
}

