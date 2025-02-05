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
	 {sf::Keyboard::Up, "Haut"}, {sf::Keyboard::Down, "Bas"},{sf::Keyboard::Right, "Droite"},{sf::Keyboard::Left, "Gauche"},
};

void OptionsMenu::initButtons()
{
	std::vector<std::string> optionsButtons = { "Volume", "Touches", "Retour" };
	for (size_t i = 0; i < optionsButtons.size(); i++) {
		sf::Text button;
		button.setFont(font);
		button.setString(optionsButtons[i]);
		button.setCharacterSize(50);
		button.setFillColor(sf::Color(24, 99, 68));

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
		button.setFillColor(sf::Color(24, 99, 68));

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
	volumeMusicSlider.setFillColor(sf::Color(50, 50, 50));
	updateCursorVolumeMusic();

	volumeSoundBar.setSize(sf::Vector2f(300, 10));
	volumeSoundBar.setFillColor(sf::Color(128, 128, 128));
	volumeSoundBar.setPosition(810, 550);

	volumeSoundSlider.setSize(sf::Vector2f(20, 30));
	volumeSoundSlider.setFillColor(sf::Color(50, 50, 50));
	updateCursorVolumeSound();

	musicVolumeText.setFont(font);
	musicVolumeText.setCharacterSize(30);
	musicVolumeText.setFillColor(sf::Color(50, 50, 50));
	musicVolumeText.setPosition(volumeMusicBar.getPosition().x + volumeMusicBar.getSize().x + 20.f, 
		volumeMusicBar.getPosition().y - 15);

	soundVolumeText.setFont(font);
	soundVolumeText.setCharacterSize(30);
	soundVolumeText.setFillColor(sf::Color(50, 50, 50));
	soundVolumeText.setPosition(volumeSoundBar.getPosition().x + volumeSoundBar.getSize().x + 20.f, volumeSoundBar.getPosition().y - 15);
}

void OptionsMenu::initChangeKeysMenu()
{
	keys.clear();
	std::vector<std::string> changeKeysButtons = { "Aller vers le haut :", "Aller vers le bas :", "Aller vers la gauche :", "Aller vers la droite :" };

	for (size_t i = 0; i < changeKeysButtons.size(); i++) {
		sf::Text button;
		button.setFont(font);
		button.setString(changeKeysButtons[i]);
		button.setCharacterSize(50);
		button.setFillColor(sf::Color(24, 99, 68));

		sf::FloatRect textBounds = button.getLocalBounds();
		float x = (Config::WINDOW_WIDTH / 2.f) - (textBounds.width / 2.f) - textBounds.left;
		button.setPosition(610, 210 + static_cast<float>(i) * 100);
		buttons.push_back(button);

		sf::RectangleShape keyShape;
		keyShape.setSize(sf::Vector2f(450, 70));
		keyShape.setFillColor(sf::Color(0, 0, 0, 150));
		keyShape.setPosition(600, 200 + static_cast<float>(i) * 100);
		keyShapes.push_back(keyShape);
		
		sf::RectangleShape keyShape2;
		keyShape2.setSize(sf::Vector2f(140, 70));
		keyShape2.setFillColor(sf::Color(0, 0, 0, 150));
	
		keyShape2.setPosition(1100, 200 + static_cast<float>(i) * 100);
		keysRect.push_back(keyShape2);

		sf::Text key;
		key.setFont(font);
		key.setFillColor(sf::Color(24, 99, 68));
		key.setCharacterSize(50);
		sf::FloatRect textKeyBounds = key.getLocalBounds();
		float xKey = keyShape2.getPosition().x + (keyShape2.getSize().x - textKeyBounds.width) / 2;
		key.setPosition(xKey-10, keyShape2.getPosition().y);

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
		}
		keys.push_back(key);
	}
	returnText.setFont(font);
	returnText.setCharacterSize(50);
	returnText.setFillColor(sf::Color(168, 168, 168));
	returnText.setString("Retour");
	returnText.setPosition(800, 610);
	
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

	//game->setMusicVolume(musicVolumeLevel);

	updateCursorVolumeMusic();
	updateTextVolumeMusic();
}

void OptionsMenu::updateSoundVolume(sf::Vector2i mousePos)
{
	float newVolume = ((mousePos.x - volumeSoundBar.getPosition().x) / volumeSoundBar.getSize().x) * 100.f;
	soundVolumeLevel = std::max(0.f, std::min(newVolume, 100.f));

	//game->setSoundVolume(soundVolumeLevel);

	updateCursorVolumeSound();
	updateTextVolumeSound();
}

OptionsMenu::OptionsMenu() : musicVolumeLevel(50), soundVolumeLevel(50),isDragging(false), 
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
				keyShapes.clear();
				keysRect.clear();
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
				keyShapes.clear();
				keysRect.clear();
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
				if (keyShapes[i].getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)) || 
					buttons[i].getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)) || 
					keysRect[i].getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)) && i != 4) {
					waitingForKey = true;
					waitingForAction = i;
				}
			}
		}
		if (waitingForKey) {
			std::vector<sf::Keyboard::Key> possibleKeys = {
	  sf::Keyboard::Up, sf::Keyboard::Down, sf::Keyboard::Left, sf::Keyboard::Right,
	  sf::Keyboard::A, sf::Keyboard::B, sf::Keyboard::C, sf::Keyboard::D,
	  sf::Keyboard::E, sf::Keyboard::F, sf::Keyboard::G, sf::Keyboard::H,
	  sf::Keyboard::I, sf::Keyboard::J, sf::Keyboard::K, sf::Keyboard::L,
	  sf::Keyboard::M, sf::Keyboard::N, sf::Keyboard::O, sf::Keyboard::P,
	  sf::Keyboard::Q, sf::Keyboard::R, sf::Keyboard::S, sf::Keyboard::T,
	  sf::Keyboard::U, sf::Keyboard::V, sf::Keyboard::W, sf::Keyboard::X,
	  sf::Keyboard::Y, sf::Keyboard::Z
			};

			for (auto key : possibleKeys) {
				if (sf::Keyboard::isKeyPressed(key)) {
					handleKeyChange(waitingForAction, key);
					waitingForKey = false;
					break;
				}
			}
			
		}
	
		if (event.type == sf::Event::MouseButtonReleased) {
			if (returnText.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
				currentMenu = MenuType::OPTIONS;
				//ignoreNextClick = true;
				buttons.clear();
				keyShapes.clear();
				keysRect.clear();
				initButtons();
				waitingForKey = false;
				waitingForAction = -1;
			}
		}
		for (size_t i = 0; i < keys.size(); i++) {
			bool isHoveredText = keys[i].getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos));
			bool isHoveredShape = i < keysRect.size() && keysRect[i].getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos));

			if (isHoveredText || isHoveredShape) {
				if (i < keysRect.size()) keysRect[i].setFillColor(sf::Color::Black);
				keys[i].setFillColor(sf::Color(48, 51, 49));
			}
			else {
				if (i < keysRect.size()) keysRect[i].setFillColor(sf::Color(0, 0, 0, 150));
				keys[i].setFillColor(sf::Color(24, 99, 68));
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
	window.draw(returnButton);
	window.draw(returnText);
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
		Menu::render(window);
		window.draw(volumeMusicBar);
		window.draw(volumeMusicSlider);
		window.draw(musicVolumeText);

		window.draw(volumeSoundBar);
		window.draw(volumeSoundSlider);
		window.draw(soundVolumeText);
	
	}
	else if (currentMenu == MenuType::KEYS) {
		Menu::render(window);
		renderChangeKeysMenu(window);
		handleMouseHover(window);
	}
}

int OptionsMenu::getMusicLevel() const
{
	return musicVolumeLevel;
}

int OptionsMenu::getSoundLevel() const
{
	return soundVolumeLevel;
}
