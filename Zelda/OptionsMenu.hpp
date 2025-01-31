#pragma once
#include "stdafx.hpp"
#include "Menu.hpp"
#include "InputHandler.hpp"
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
	vector<Text> keys;
	float musicVolumeLevel;
	float soundVolumeLevel;
	bool isDragging;
	
	void initButtons() override;
	void initVolumeMenu();
	void initVolumeControl();
	void initChangeKeysMenu();

	MenuType currentMenu;

	bool waitingForKey;
	int waitingForAction;
	InputHandler inputHandler;

	bool ignoreNextClick;
public:

	OptionsMenu();

	void updateTextVolumeMusic();
	void updateTextVolumeSound();
	void updateCursorVolumeMusic();
	void updateCursorVolumeSound();
	void updateMusicVolume(Vector2i mousePos);
	void updateSoundVolume(Vector2i mousePos);

	void handleKeyChange(int actionIndex, Keyboard::Key newKey);
	int handleInput(RenderWindow& window, const Event& event) override;

	void renderChangeKeysMenu(RenderWindow& window);
	void render(RenderWindow& window) override;
};

