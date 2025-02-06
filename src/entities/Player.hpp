#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.hpp"
#include "../core/InputHandler.hpp"
#include "../systems/Physics.hpp"
#include "../objet/Inventory.hpp"
#include "../objet/Item.hpp"
#include "../map/Map.hpp"

class Player : public Entity
{
public:
    Player(sf::Vector2f position, float size, const std::string& texturePath, float hp);

    void update(float deltatime, const std::vector<sf::Sprite>& bushes) override;
    void draw(sf::RenderWindow& window) override;
    void handleInput(float deltatime);
    void setSpeed(float amount);
    sf::Vector2f getMovementDelta(float deltatime) const;
    void checkCollisionWithWalls(const std::vector<sf::RectangleShape>& walls);
    void checkCollisionWithMap(const std::vector<sf::Sprite>& bushes);
    void checkDoor(const std::vector<Map::Door>& doors);
    void addItemToInventory(const Item<int>& item) { inventory.addItem(item); }
    void removeItemFromInventory(const std::string& itemName) { inventory.removeItem(itemName); }
    bool hasItemInInventory(const std::string& itemName) const { return inventory.hasItem(itemName); }
    void showInventory() const { inventory.displayInventory(); }


    const sf::Sprite& getSprite() const { return player; }
    bool hasKey;
    
    void reset();

    void damage(int damages);

    sf::Vector2f getPosition() const;
    float getHealth() const;
    float getSpeed() const;
    sf::FloatRect getGlobalBounds() const;
    bool isDead() const;

    void setPosition(const sf::Vector2f& position);

    //id setSpeed(int speed);

    sf::FloatRect getHitbox() const;
    void drawHitBox(sf::RenderWindow& window);
    const Inventory<int>& getInventory() const { return inventory; }
private :
    Inventory<int>inventory;

protected:
    sf::Sprite player;
    sf::Texture texture;
    sf::Vector2f previousPosition;
    
    sf::Texture fullHeartTexture, halfHeartTexture, emptyHeartTexture;
    std::vector<sf::Sprite> hearts;
   
    sf::Texture textureLife;
    sf::Sprite life;
    int maxHp;
    float damageCooldown;

    Physics physics;
    sf::FloatRect hitbox;
    void initHeartTexture();
    void initLifeTexture();

};