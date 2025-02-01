#include "../core/InputHandler.hpp"

std::map<InputHandler::Action, sf::Keyboard::Key> InputHandler::keyBindings;

InputHandler::InputHandler()
{
    keyBindings[Action::UP] = sf::Keyboard::Z;
    keyBindings[Action::DOWN] = sf::Keyboard::S;
    keyBindings[Action::LEFT] = sf::Keyboard::Q;
    keyBindings[Action::RIGHT] = sf::Keyboard::D;
}

sf::Vector2f InputHandler::getMovementDirection() {
    sf::Vector2f direction(0.f, 0.f);

    if (sf::Keyboard::isKeyPressed(keyBindings[Action::UP])) {
        direction.y -= 1.f;
    }
    if (sf::Keyboard::isKeyPressed(keyBindings[Action::DOWN])) {
        direction.y += 1.f;
    }
    if (sf::Keyboard::isKeyPressed(keyBindings[Action::LEFT])) {
        direction.x -= 1.f;
    }
    if (sf::Keyboard::isKeyPressed(keyBindings[Action::RIGHT])) {
        direction.x += 1.f;
    }

    if (direction.x != 0.f || direction.y != 0.f) {
        float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
        direction /= length;
    }

    return direction;
}

void InputHandler::remapKey(Action action, sf::Keyboard::Key newKey)
{
    keyBindings[action] = newKey;
}

sf::Keyboard::Key InputHandler::getKeyForAction(Action action)
{
    return keyBindings[action];
}