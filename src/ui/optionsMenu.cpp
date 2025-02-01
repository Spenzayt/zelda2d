#include "OptionsMenu.hpp"
#include <iostream>

std::map<sf::Keyboard::Key, std::string> keyNames = {
	{sf::Keyboard::A, "A"}, {sf::Keyboard::B, "B"}, {sf::Keyboard::C, "C"},
	{sf::Keyboard::D, "D"}, {sf::Keyboard::E, "E"}, {sf::Keyboard::F, "F"},
	{sf::Keyboard::G, "G"}, {sf::Keyboard::H, "H"}, {sf::Keyboard::I, "I"},
	{sf::Keyboard::J, "J"}, {sf::Keyboard::K, "K"}, {sf::Keyboard::L, "L"},
	{sf::Keyboard::M, "M"}, {sf::Keyboard::N, "N"}, {sf::Keyboard::O, "O"},
	{sf::Keyboard::P, "P"}, {sf::Keyboard::Q, "Q"}, {sf::Keyboard::R, "R"},
	{sf::Keyboard::S, "S"}, {sf::Keyboard::T, "T"}, {sf::Keyboard::U, "U"},
	{sf::Keyboard::V, "V"}, {sf::Keyboard::W, "W"}, {sf::Keyboard::X, "X"},
	{sf::Keyboard::Y, "Y"}, {sf::Keyboard::Z, "Z"}, {sf::Keyboard::Num0, "Num0"},
	{sf::Keyboard::Num1, "Num1"}, {sf::Keyboard::Num2, "Num2"}, {sf::Keyboard::Num3, "Num3"},
	{sf::Keyboard::Num4, "Num4"}, {sf::Keyboard::Num5, "Num5"}, {sf::Keyboard::Num6, "Num6"},
	{sf::Keyboard::Num7, "Num7"}, {sf::Keyboard::Num8, "Num8"}, {sf::Keyboard::Num9, "Num9"},
};

void OptionsMenu::initButtons()
{
	std::vector<std::string> optionsButtons = { "Volume", "Touches", "Retour" };
	for (size_t i = 0; i < optionsButtons.size(); i++) {
		sf::Text button;
		button.setFont(font);
		button.setString(optionsButtons[i]);
		button.setCharacterSize(50);
		button.setFillColor(sf::Color(168, 168, 168));

		sf::FloatRect textBounds = button.getLocalBounds();
		float x = (Config::WINDOW_WIDTH / 2.f) - (textBounds.width / 2.f) - textBounds.left;
		button.setPosition(x, 400 + static_cast<float>(i) * 80);
		buttons.push_back(button);
	}
}

void OptionsMenu::initVolumeMenu()
{
	std::vector<std::string> volumeButtons = { "Musique", "Sons", "Retour" };
	for (size_t i = 0; i < volumeButtons.size(); i++) {
		sf::Text button;
		button.setFont(font);
		button.setString(volumeButtons[i]);
		button.setCharacterSize(50);
		button.setFillColor(sf::Color(168, 168, 168));

		sf::FloatRect textBounds = button.getLocalBounds();
		float x = (Config::WINDOW_WIDTH / 2.f) - (textBounds.width / 2.f) - textBounds.left;
		button.setPosition(x, 400 + static_cast<float>(i) * 90);
		buttons.push_back(button);
	}
	initVolumeControl();
	updateTextVolumeMusic();
	updateTextVolumeSound();
}

void OptionsMenu::initVolumeControl()
{
	volumeMusicBar.setSize(sf::Vector2f(300, 10));
	volumeMusicBar.setFillColor(sf::Color(128, 128, 128));
	volumeMusicBar.setPosition(810, 470);

	volumeMusicSlider.setSize(sf::Vector2f(20, 30));
	volumeMusicSlider.setFillColor(sf::Color::White);
	updateCursorVolumeMusic();

	volumeSoundBar.setSize(sf::Vector2f(300, 10));
	volumeSoundBar.setFillColor(sf::Color(128, 128, 128));
	volumeSoundBar.setPosition(810, 550);

	volumeSoundSlider.setSize(sf::Vector2f(20, 30));
	volumeSoundSlider.setFillColor(sf::Color::White);
	updateCursorVolumeSound();

	musicVolumeText.setFont(font);
	musicVolumeText.setCharacterSize(30);
	musicVolumeText.setFillColor(sf::Color::White);
	musicVolumeText.setPosition(volumeMusicBar.getPosition().x + volumeMusicBar.getSize().x + 20.f, 
		volumeMusicBar.getPosition().y - 15);

	soundVolumeText.setFont(font);
	soundVolumeText.setCharacterSize(30);
	soundVolumeText.setFillColor(sf::Color::White);
	soundVolumeText.setPosition(volumeSoundBar.getPosition().x + volumeSoundBar.getSize().x + 20.f, volumeSoundBar.getPosition().y - 15);
}

void OptionsMenu::initChangeKeysMenu()
{
	keys.clear();
	std::vector<std::string> changeKeysButtons = { "Aller vers le haut :", "Aller vers le bas :", "Aller vers la gauche :", "Aller vers la droite :", "Retour" };

	for (size_t i = 0; i < changeKeysButtons.size(); i++) {
		sf::Text button;
		button.setFont(font);
		button.setString(changeKeysButtons[i]);
		button.setCharacterSize(50);
		button.setFillColor(sf::Color(168, 168, 168));

		sf::FloatRect textBounds = button.getLocalBounds();
		float x = (Config::WINDOW_WIDTH / 2.f) - (textBounds.width / 2.f) - textBounds.left;
		button.setPosition(x, 300 + static_cast<float>(i) * 80);
		buttons.push_back(button);

		sf::Text key;
		key.setFont(font);
		key.setFillColor(sf::Color(168, 168, 168));
		key.setCharacterSize(50);
		key.setPosition(button.getPosition().x + button.getLocalBounds().width + 50.f, button.getPosition().y);
		switch (i) {
		case 0:
			key.setString(keyNames[inputHandler.getKeyForAction(InputHandler::Action::UP)]);
			break;
		case 1:
			key.setString(keyNames[inputHandler.getKeyForAction(InputHandler::Action::DOWN)]);
			break;
		case 2:
			key.setString(keyNames[inputHandler.getKeyForAction(InputHandler::Action::LEFT)]);

			break;
		case 3:
			key.setString(keyNames[inputHandler.getKeyForAction(InputHandler::Action::RIGHT)]);
			break;
		case 4:
			key.setString("");
			break;
		}
		keys.push_back(key);
	}
	waitingForKey = false;
	waitingForAction = -1;
}

void OptionsMenu::updateTextVolumeMusic()
{
	musicVolumeText.setString(std::to_string((int)musicVolumeLevel));
}

void OptionsMenu::updateTextVolumeSound()
{
	soundVolumeText.setString(std::to_string((int)soundVolumeLevel));
}

void OptionsMenu::updateCursorVolumeMusic()
{
	float x = volumeMusicBar.getPosition().x + (musicVolumeLevel / 100.f) * volumeMusicBar.getSize().x;
	volumeMusicSlider.setPosition(x - 5.f, volumeMusicBar.getPosition().y - 10.f);
}

void OptionsMenu::updateCursorVolumeSound()
{
	float x = volumeSoundBar.getPosition().x + (soundVolumeLevel / 100.f) * volumeSoundBar.getSize().x;
	volumeSoundSlider.setPosition(x - 5.f, volumeSoundBar.getPosition().y - 10.f);
}

void OptionsMenu::updateMusicVolume(sf::Vector2i mousePos)
{
	float newVolume = ((mousePos.x - volumeMusicBar.getPosition().x) / volumeMusicBar.getSize().x) * 100.f;
	musicVolumeLevel = std::max(0.f, std::min(newVolume, 100.f));

	updateCursorVolumeMusic();
	updateTextVolumeMusic();
}

void OptionsMenu::updateSoundVolume(sf::Vector2i mousePos)
{
	float newVolume = ((mousePos.x - volumeSoundBar.getPosition().x) / volumeSoundBar.getSize().x) * 100.f;
	soundVolumeLevel = std::max(0.f, std::min(newVolume, 100.f));

	updateCursorVolumeSound();
	updateTextVolumeSound();
}

OptionsMenu::OptionsMenu() : musicVolumeLevel(100), soundVolumeLevel(100),isDragging(false), 
ignoreNextClick(true), isDraggingMusic(false), isDraggingSound(false)
{
	initButtons();
}

void OptionsMenu::handleKeyChange(int actionIndex, sf::Keyboard::Key newKey)
{
	for (int i = 0; i < 4; i++) {
		if (inputHandler.getKeyForAction(static_cast<InputHandler::Action>(i)) == newKey) {
			inputHandler.remapKey(static_cast<InputHandler::Action>(i), sf::Keyboard::Unknown);
			keys[i].setString("");
		}
	}
	if (actionIndex < 4) {
		inputHandler.remapKey(static_cast<InputHandler::Action>(actionIndex), newKey);

		keys[actionIndex].setString(keyNames[newKey]);
	}
}

int OptionsMenu::handleInput(sf::RenderWindow& window, const sf::Event& event)
{
	sf::Vector2i mousePos = sf::Mouse::getPosition(window);
	if (ignoreNextClick) {
		if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
			ignoreNextClick = false;
		}
		return - 1;
	}
	if (currentMenu == MenuType::OPTIONS) {
		if (event.type == sf::Event::MouseButtonPressed) {
			if (buttons[0].getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
				currentMenu = MenuType::VOLUME;
				ignoreNextClick = true;
				buttons.clear();
				initVolumeMenu();
			}
			else if (buttons[1].getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
				currentMenu = MenuType::KEYS;
				ignoreNextClick = true;
				buttons.clear();
				initChangeKeysMenu();
			}
			else if (buttons[2].getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
				ignoreNextClick = true;
				return 2;
			}
		}

	}
	else if (currentMenu == MenuType::VOLUME) {
		if (event.type == sf::Event::MouseButtonPressed) {
			if (buttons[2].getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
				currentMenu = MenuType::OPTIONS;
				//ignoreNextClick = true;
				buttons.clear();
				resetCooldown();
				initButtons();
			}
			if (volumeMusicSlider.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)) ||
				volumeMusicBar.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
				isDraggingMusic = true;
				updateMusicVolume(mousePos);
			}
			if (volumeSoundSlider.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)) ||
				volumeSoundBar.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
				isDraggingSound = true;
				updateSoundVolume(mousePos);
			}
		}
		if (event.type == sf::Event::MouseButtonReleased) {
			isDraggingMusic = false;
			isDraggingSound = false;
		}

		if (event.type == sf::Event::MouseMoved) {
			if (isDraggingMusic) {
				updateMusicVolume(mousePos);
			}
			if (isDraggingSound) {
				updateSoundVolume(mousePos);
			}
		}
		
	}
	else if (currentMenu == MenuType::KEYS) {
		if (event.type == sf::Event::MouseButtonPressed) {
			for (size_t i = 0; i < keys.size(); i++) {
				if (keys[i].getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)) 
					|| buttons[i].getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)) && i != 4) {
					waitingForKey = true;
					waitingForAction = i;
				}
			}
		}
		if (waitingForKey) {
			for (int key = sf::Keyboard::A; key <= sf::Keyboard::Z; key++) {
				if (sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(key))) {
					handleKeyChange(waitingForAction, static_cast<sf::Keyboard::Key>(key));
					waitingForKey = false;
					break;
				}
			}
		}
	
		if (event.type == sf::Event::MouseButtonReleased) {
			if (buttons[4].getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
	
				currentMenu = MenuType::OPTIONS;
				//ignoreNextClick = true;
				buttons.clear();
				initButtons();
				waitingForKey = false;
				waitingForAction = -1;
			}
		}
		for (auto& key : keys) {
			if (key.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
				key.setFillColor(sf::Color::White);
			}
			else {
				key.setFillColor(sf::Color(168, 168, 168));
			}
		}
	}

	return -1;
}

void OptionsMenu::renderChangeKeysMenu(sf::RenderWindow& window)
{
	for (size_t i = 0; i < buttons.size(); i++) {
		window.draw(keys[i]); 
	}
	if (waitingForKey) {
		sf::Text waitText;
		waitText.setFont(font);
		waitText.setString("Appuyez sur une touche...");
		waitText.setFillColor(sf::Color(5, 158, 41));
		waitText.setCharacterSize(50);
		sf::FloatRect waitBounds = waitText.getLocalBounds();
		float x = (Config::WINDOW_WIDTH / 2.f) - (waitBounds.width / 2.f) - waitBounds.left;
		waitText.setPosition(x, 950);
		window.draw(waitText);
	}
}

void OptionsMenu::render(sf::RenderWindow& window)
{
	if (currentMenu == MenuType::OPTIONS) {
		Menu::render(window);
	}
	else if (currentMenu == MenuType::VOLUME) {
		window.draw(volumeMusicBar);
		window.draw(volumeMusicSlider);
		window.draw(musicVolumeText);

		window.draw(volumeSoundBar);
		window.draw(volumeSoundSlider);
		window.draw(soundVolumeText);
		Menu::render(window);
	}
	else if (currentMenu == MenuType::KEYS) {
		renderChangeKeysMenu(window);
		Menu::render(window);
	}
}