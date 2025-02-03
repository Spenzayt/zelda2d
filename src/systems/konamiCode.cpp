#include "KonamiCode.hpp"
#include <iostream>

KonamiCode::KonamiCode() : activated(false) {
    konamiCode = {
        sf::Keyboard::Up, sf::Keyboard::Up,
        sf::Keyboard::Down, sf::Keyboard::Down,
        sf::Keyboard::Left, sf::Keyboard::Right,
        sf::Keyboard::Left, sf::Keyboard::Right,
        sf::Keyboard::B, sf::Keyboard::A
    };
}

bool KonamiCode::isActivated(const sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        inputSequence.push_back(event.key.code);

        if (inputSequence.size() > konamiCode.size()) {
            inputSequence.erase(inputSequence.begin());
        }

        if (inputSequence == konamiCode) {
            inputSequence.clear();
            flipFlop();
            return true;
        }
    }

    return false;
}

bool KonamiCode::isKonamiActivated() const {
    return activated;
}

void KonamiCode::flipFlop() {
    activated = !activated;
    std::cout << "Konami Code is now " << (activated ? "activated" : "deactivated") << std::endl;
}

void KonamiCode::setDebugAction(sf::Keyboard::Key key, std::function<void()> action) {
    debugActions[key] = action;
}

void KonamiCode::handleDebugActions(const sf::Event& event) {
    if (event.type == sf::Event::KeyPressed && activated) {
        auto it = debugActions.find(event.key.code);
        if (it != debugActions.end()) {
            it->second();
        }
    }
}