#pragma once
#include "stdafx.hpp"
class Menu {
protected:
    Font font;
    std::vector<Text> buttons;

    // temps entre chaque clic 
    Clock cooldownMouseClock;
    const Time cooldownMouse;

    virtual void initButtons() = 0;
void initFont();
public:
    Menu();

    virtual int handleInput(RenderWindow& window, const Event& event) = 0;
    virtual void handleMouseHover(const RenderWindow& window);

    virtual void render(RenderWindow& window);

    bool isCooldownActive();
    void resetCooldown();
};

