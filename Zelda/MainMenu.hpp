#pragma once
#include "stdafx.hpp"
#include "Menu.hpp"
class MainMenu : public Menu {
private:
    void initButtons() override;
public:
    MainMenu();

    int handleInput(RenderWindow& window, const Event& event) override;
};

