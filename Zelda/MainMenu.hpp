#pragma once
#include "stdafx.hpp"
#include "Menu.hpp"
class MainMenu : public Menu {
private:
    void initButtons() override;
public:
    MainMenu(std::shared_ptr<Font> sharedFont);

    int handleInput(RenderWindow& window, const Event& event) override;
};

