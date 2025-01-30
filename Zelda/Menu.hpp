#pragma once
#include "stdafx.hpp"
class Menu {
protected:
    std::shared_ptr<Font> font;
    std::vector<Text> buttons;

    // temps entre chaque clic 
    Clock cooldownMouseClock;

    virtual void initButtons() = 0;
public:
    Menu(std::shared_ptr<Font> sharedFont);

    virtual int handleInput(RenderWindow& window, const Event& event) = 0;
    virtual void handleMouseHover(const RenderWindow& window);

    virtual void render(RenderWindow& window);
};

