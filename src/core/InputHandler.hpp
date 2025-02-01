#ifndef INPUT_HANDLER_HPP
#define INPUT_HANDLER_HPP

#include <SFML/Graphics.hpp>
#include <map>

class InputHandler {
public:
    enum Action {
        UP,
        DOWN,
        LEFT,
        RIGHT
    };
    InputHandler();
    static sf::Vector2f getMovementDirection();

    static void remapKey(Action action, sf::Keyboard::Key newKey);
    static sf::Keyboard::Key getKeyForAction(Action action);
private:
    static std::map<Action, sf::Keyboard::Key> keyBindings;
};

#endif // INPUT_HANDLER_HPP