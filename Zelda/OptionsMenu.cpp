#include "OptionsMenu.hpp"


map<Keyboard::Key, string> keyNames = {
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
	vector<string> optionsButtons = { "Volume", "Touches", "Retour" };
	float windowWidth = 1920.f;
	for (size_t i = 0; i < optionsButtons.size(); i++) {
		Text button;
		button.setFont(font);
		button.setString(optionsButtons[i]);
		button.setCharacterSize(50);
		button.setFillColor(Color(168, 168, 168));

		FloatRect textBounds = button.getLocalBounds();
		float x = (windowWidth / 2.f) - (textBounds.width / 2.f) - textBounds.left;
		button.setPosition(x, 400 + static_cast<float>(i) * 80);
		buttons.push_back(button);
	}

}

void OptionsMenu::initVolumeMenu()
{
	vector<string> volumeButtons = { "Musique", "Sons", "Retour" };
	float windowWidth = 1920.f;
	for (size_t i = 0; i < volumeButtons.size(); i++) {
		Text button;
		button.setFont(font);
		button.setString(volumeButtons[i]);
		button.setCharacterSize(50);
		button.setFillColor(Color(168, 168, 168));

		FloatRect textBounds = button.getLocalBounds();
		float x = (windowWidth / 2.f) - (textBounds.width / 2.f) - textBounds.left;
		button.setPosition(x, 400 + static_cast<float>(i) * 80);
		buttons.push_back(button);
	}
	initVolumeControl();
}

void OptionsMenu::initVolumeControl()
{
	volumeMusicBar.setSize(Vector2f(300, 10));
	volumeMusicBar.setFillColor(Color(128, 128, 128));
	volumeMusicBar.setPosition(810, 460);

	volumeMusicSlider.setSize(Vector2f(20, 30));
	volumeMusicSlider.setFillColor(Color::White);
	updateCursorVolumeMusic();

	volumeSoundBar.setSize(Vector2f(300, 10));
	volumeSoundBar.setFillColor(Color(128, 128, 128));
	volumeSoundBar.setPosition(810, 540);

	volumeSoundSlider.setSize(Vector2f(20, 30));
	volumeSoundSlider.setFillColor(Color::White);
	updateCursorVolumeSound();

	musicVolumeText.setFont(font);
	musicVolumeText.setCharacterSize(30);
	musicVolumeText.setFillColor(Color::White);
	musicVolumeText.setPosition(volumeMusicBar.getPosition().x + volumeMusicBar.getSize().x + 20.f, 
		volumeMusicBar.getPosition().y - 15);

	soundVolumeText.setFont(font);
	soundVolumeText.setCharacterSize(30);
	soundVolumeText.setFillColor(Color::White);
	soundVolumeText.setPosition(volumeSoundBar.getPosition().x + volumeSoundBar.getSize().x + 20.f, volumeSoundBar.getPosition().y - 15);
}

void OptionsMenu::initChangeKeysMenu()
{
	keys.clear();
	vector<string> changeKeysButtons = { "Aller vers le haut :", "Aller vers le bas :", "Aller vers la gauche :", "Aller vers la droite :", "Retour" };
	float windowWidth = 1920.f;

	for (size_t i = 0; i < changeKeysButtons.size(); i++) {
		Text button;
		button.setFont(font);
		button.setString(changeKeysButtons[i]);
		button.setCharacterSize(50);
		button.setFillColor(Color(168, 168, 168));

		FloatRect textBounds = button.getLocalBounds();
		float x = (windowWidth / 2.f) - (textBounds.width / 2.f) - textBounds.left;
		button.setPosition(x, 300 + static_cast<float>(i) * 80);
		buttons.push_back(button);

		Text key;
		key.setFont(font);
		key.setFillColor(Color::White);
		key.setCharacterSize(50);
		key.setPosition(button.getPosition().x + button.getLocalBounds().width + 10.f, button.getPosition().y);
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
	musicVolumeText.setString(to_string((int)musicVolumeLevel));
}

void OptionsMenu::updateTextVolumeSound()
{
	soundVolumeText.setString(to_string((int)soundVolumeLevel));
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

void OptionsMenu::updateMusicVolume(Vector2i mousePos)
{
	float newVolume = ((mousePos.x - volumeMusicBar.getPosition().x) / volumeMusicBar.getSize().x) * 100.f;
	musicVolumeLevel = max(0.f, min(newVolume, 100.f)); 

	updateCursorVolumeMusic();
	updateTextVolumeMusic();
}

void OptionsMenu::updateSoundVolume(Vector2i mousePos)
{
	float newVolume = ((mousePos.x - volumeSoundBar.getPosition().x) / volumeSoundBar.getSize().x) * 100.f;
	soundVolumeLevel = max(0.f, min(newVolume, 100.f));

	updateCursorVolumeSound();
	updateTextVolumeSound();
}

OptionsMenu::OptionsMenu() : musicVolumeLevel(100), soundVolumeLevel(100),isDragging(false), ignoreNextClick(true)
{
	initButtons();
}

void OptionsMenu::handleKeyChange(int actionIndex, Keyboard::Key newKey)
{

	if (actionIndex < 4) {
		inputHandler.remapKey(static_cast<InputHandler::Action>(actionIndex), newKey);

		keys[actionIndex].setString(keyNames[newKey]);
	}
}

int OptionsMenu::handleInput(RenderWindow& window, const Event& event)
{
	Vector2i mousePos = Mouse::getPosition(window);
	if (ignoreNextClick) {
		if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
			ignoreNextClick = false;
		}
		return - 1;
	}
	if (currentMenu == MenuType::OPTIONS) {
		if (event.type == Event::MouseButtonPressed) {
			if (buttons[0].getGlobalBounds().contains(static_cast<Vector2f>(mousePos))) {
				currentMenu = MenuType::VOLUME;
				ignoreNextClick = true;
				buttons.clear();
				initVolumeMenu();
			}
			else if (buttons[1].getGlobalBounds().contains(static_cast<Vector2f>(mousePos))) {
				currentMenu = MenuType::KEYS;
				ignoreNextClick = true;
				buttons.clear();
				initChangeKeysMenu();
			}
			else if (buttons[2].getGlobalBounds().contains(static_cast<Vector2f>(mousePos))) {
				ignoreNextClick = true;
				return 2;
			}
		}

	}
	else if (currentMenu == MenuType::VOLUME) {
		if (event.type == Event::MouseButtonPressed) {
			if (buttons[2].getGlobalBounds().contains(static_cast<Vector2f>(mousePos))) {
				currentMenu = MenuType::OPTIONS;
				//ignoreNextClick = true;
				buttons.clear();
				resetCooldown();
				initButtons();
			}
			if (volumeMusicSlider.getGlobalBounds().contains(static_cast<Vector2f>(mousePos)) ||
				volumeMusicBar.getGlobalBounds().contains(static_cast<Vector2f>(mousePos))) {
				isDragging = true;
				updateMusicVolume(mousePos);
			}
			if (volumeSoundSlider.getGlobalBounds().contains(static_cast<Vector2f>(mousePos)) ||
				volumeSoundBar.getGlobalBounds().contains(static_cast<Vector2f>(mousePos))) {
				isDragging = true;
				updateSoundVolume(mousePos);
			}
		}
		if (event.type == Event::MouseButtonReleased) {
			isDragging = false;
		}

		if (event.type == Event::MouseMoved && isDragging) {
			if (volumeMusicSlider.getGlobalBounds().contains(static_cast<Vector2f>(mousePos))) {
				updateMusicVolume(mousePos);
			}
			if (volumeSoundSlider.getGlobalBounds().contains(static_cast<Vector2f>(mousePos))) {
				updateSoundVolume(mousePos);
			}
		}
		
	}
	else if (currentMenu == MenuType::KEYS) {
		if (event.type == Event::MouseButtonPressed) {
			for (size_t i = 0; i < buttons.size(); i++) {
				if (buttons[i].getGlobalBounds().contains(static_cast<Vector2f>(mousePos)) && i != 4) {
					waitingForKey = true;
					waitingForAction = i;
				}
			}
		}
		if (waitingForKey) {
			for (int key = Keyboard::A; key <= Keyboard::Z; key++) {
				if (Keyboard::isKeyPressed(static_cast<Keyboard::Key>(key))) {
					handleKeyChange(waitingForAction, static_cast<Keyboard::Key>(key));
					waitingForKey = false;
					break;
				}
			}
		}
	
		if (event.type == Event::MouseButtonReleased) {
			if (buttons[4].getGlobalBounds().contains(static_cast<Vector2f>(mousePos))) {
	
				currentMenu = MenuType::OPTIONS;
				//ignoreNextClick = true;
				buttons.clear();
				initButtons();
				waitingForKey = false;
				waitingForAction = -1;
			}
		}
	}

	return -1;
}

void OptionsMenu::renderChangeKeysMenu(RenderWindow& window)
{
	for (size_t i = 0; i < buttons.size(); i++) {
		window.draw(keys[i]); 
	}
	float windowWidth = 1920.f;
	if (waitingForKey) {
		Text waitText;
		waitText.setFont(font);
		waitText.setString("Appuyez sur une touche...");
		waitText.setFillColor(Color(5, 158, 41));
		waitText.setCharacterSize(50);
		FloatRect waitBounds = waitText.getLocalBounds();
		float x = (windowWidth / 2.f) - (waitBounds.width / 2.f) - waitBounds.left;
		waitText.setPosition(x, 950);
		window.draw(waitText);
	}
}

void OptionsMenu::render(RenderWindow& window)
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


