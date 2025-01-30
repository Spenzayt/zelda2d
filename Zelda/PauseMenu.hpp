#pragma once
#include "stdafx.hpp"
#include "Menu.hpp"
class PauseMenu : public Menu
{
private:
	void initButtons() override;
public:
	PauseMenu();

	int handleInput(RenderWindow& window, const Event& event) override;
};

