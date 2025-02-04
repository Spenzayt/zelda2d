#include "Player.hpp"
#include <iostream>


Player::Player(sf::Vector2f spawnposition, float size, const std::string& texturePath, float hp) : hasKey(false)
{
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

    for (int i = 0; i < maxHp / 10; i++) {
        sf::Sprite heart(fullHeartTexture);
        hearts.push_back(heart);
    }
 

    player.setTexture(texture);
    player.setScale(size / static_cast<float>(texture.getSize().x), size / static_cast<float>(texture.getSize().y));
    player.setPosition(position);

    hitbox = sf::FloatRect(position.x, position.y, size, size);

    physics.loadCollisionImage();
    physics.resizeCollisionImage(1539*4, 2053*4);
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

void Player::increaseSpeed(float amount) {
    speed += amount;
}

void Player::collectKey() {
    hasKey = true;
    std::cout << "Player has the key!" << std::endl;
}

void Player::draw(sf::RenderWindow& window) {
    window.draw(player);

    static sf::Font font;
    if (font.getInfo().family.empty()) {
        if (!font.loadFromFile("assets/fonts/arial.ttf")) {
            std::cerr << "Error loading font!" << std::endl;
            return;
        }
    }

    float heartSpacing = 40.f;
    float marginTop = 50.f;
    float marginRight = 10.f;

    sf::Vector2f viewSize = window.getView().getSize();
    sf::Vector2f viewCenter = window.getView().getCenter();

    float x = viewCenter.x + (viewSize.x / 2) - marginRight - (maxHp / 10) * heartSpacing;

        for (int i = 0; i < maxHp / 10; i++) {
            hearts[i].setPosition(x + i * heartSpacing, viewCenter.y - (viewSize.y / 2) + marginTop) ;

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
    text.setString("Player Position: (" + std::to_string((int)position.x) + ", " + std::to_string((int)position.y) + ")");
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);

    sf::View currentView = window.getView();
    sf::Vector2f center = currentView.getCenter();
    text.setPosition(center.x - window.getSize().x / 2 + 10.f, center.y - window.getSize().y / 2 + 10.f);

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

void Player::initHeartTexture()
{
    if (!fullHeartTexture.loadFromFile("assets/images/interface/fullheart.png") ||
        !halfHeartTexture.loadFromFile("assets/images/interface/halfheart.png") || 
    !emptyHeartTexture.loadFromFile("assets/images/interface/emptyheart.png")) {
        std::cerr << "Error loading the heart textures !" << std::endl;
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
    sf::FloatRect hitbox(position.x, position.y, player.getGlobalBounds().width, player.getGlobalBounds().height);
    hitbox.left += hitbox.width * 0.2f;
    hitbox.top += hitbox.height * 0.2f;
    hitbox.width *= 0.6f;
    hitbox.height *= 0.6f;
    return hitbox;
}

void Player::checkHouseEntry(const sf::FloatRect& houseEntry, PlayerLocation& location) {
    if (getHitbox().intersects(houseEntry)) {
        location = PlayerLocation::INSIDE_HOUSE;
        setPosition(sf::Vector2f(415, 560));
    }
}

void Player::checkHouseExit(const sf::FloatRect& houseExit, PlayerLocation& location) {
    if (getHitbox().intersects(houseExit)) {
        location = PlayerLocation::OUTSIDE;
        setPosition(sf::Vector2f(4850, 5200));
    }
}