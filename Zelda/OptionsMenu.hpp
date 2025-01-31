#pragma once
#include "stdafx.hpp"
#include "Menu.hpp"
class OptionsMenu : public Menu
{
public:
	enum MenuType {
		OPTIONS,
		VOLUME,
		KEYS
	};
private:
	//Text textVolume;
	//float volumeLevel;
	RectangleShape volumeMusicBar;
	RectangleShape volumeMusicSlider;
	RectangleShape volumeSoundBar;
	RectangleShape volumeSoundSlider;

	Text musicVolumeText;
	Text soundVolumeText;
	float musicVolumeLevel;
	float soundVolumeLevel;
	bool isDragging;
	
	void initButtons() override;
	void initVolumeMenu();
	void initVolumeControl();

	MenuType currentMenu;
public:

	OptionsMenu();

	void updateTextVolumeMusic();
	void updateTextVolumeSound();
	void updateCursorVolumeMusic();
	void updateCursorVolumeSound();
	void updateMusicVolume(Vector2i mousePos);
	void updateSoundVolume(Vector2i mousePos);
	int handleInput(RenderWindow& window, const Event& event) override;
	void render(RenderWindow& window) override;
};

