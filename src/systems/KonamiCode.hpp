#ifndef KONAMI_HPP
#define KONAMI_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <unordered_map>
#include <functional>

class KonamiCode {
public:
    KonamiCode();

    bool isActivated(const sf::Event& event);
    bool isKonamiActivated() const;
    void flipFlop();

    void setDebugAction(sf::Keyboard::Key key, std::function<void()> action);
    void handleDebugActions(const sf::Event& event);

private:
    std::vector<sf::Keyboard::Key> konamiCode;
    std::vector<sf::Keyboard::Key> inputSequence;
    bool activated;
    std::unordered_map<sf::Keyboard::Key, std::function<void()>> debugActions;
};

#endif // KONAMI_HPP