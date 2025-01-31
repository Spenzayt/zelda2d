#pragma once
#include "stdafx.hpp"

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

   static void remapKey(Action action, Keyboard::Key newKey);
   static Keyboard::Key getKeyForAction(Action action);
private:
    static map<Action, Keyboard::Key> keyBindings;
};
