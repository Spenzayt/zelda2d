#ifndef OPTION_MENU_HPP
#define OPTION_MENU_HPP

#include <SFML/Graphics.hpp>
#include <algorithm> 
#include "Menu.hpp"
#include "../core/InputHandler.hpp"
#include "../systems/SoundManager.hpp"

class OptionsMenu : public Menu
{
public:
	enum MenuType {
		OPTIONS,
		VOLUME,
		KEYS
	};
private:
	sf::RectangleShape volumeMusicBar;
	sf::RectangleShape volumeMusicSlider;
	sf::RectangleShape volumeSoundBar;
	sf::RectangleShape volumeSoundSlider;

	sf::Text musicVolumeText;
	sf::Text soundVolumeText;
	std::vector<sf::Text> keys;
	float musicVolumeLevel;
	float soundVolumeLevel;
	bool isDragging;
	bool isDraggingMusic;
	bool isDraggingSound;
	
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
	void updateMusicVolume(sf::Vector2i mousePos);
	void updateSoundVolume(sf::Vector2i mousePos);

	void handleKeyChange(int actionIndex, sf::Keyboard::Key newKey);
	int handleInput(sf::RenderWindow& window, const sf::Event& event) override;

	void renderChangeKeysMenu(sf::RenderWindow& window);
	void render(sf::RenderWindow& window) override;

	int getMusicLevel() const;
	int getSoundLevel() const;

};

#endif // OPTION_MENU_HPP