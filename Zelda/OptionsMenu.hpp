#pragma once
#include "stdafx.hpp"
#include "Menu.hpp"
class OptionsMenu : public Menu
{
private:
	Text textVolume;
	float volumeLevel;


	void initButtons() override;
	void updateTextVolume();
public:
	OptionsMenu();

	int handleInput(RenderWindow& window, const Event& event) override;
	//void render(RenderWindow& window) override;
};

