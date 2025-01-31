#include "OptionsMenu.hpp"

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

OptionsMenu::OptionsMenu() : musicVolumeLevel(100), soundVolumeLevel(100),isDragging(false)
{
	initButtons();
}

int OptionsMenu::handleInput(RenderWindow& window, const Event& event)
{
	Vector2i mousePos = Mouse::getPosition(window);

	if (currentMenu == MenuType::OPTIONS) {
		if (event.type == Event::MouseButtonPressed) {
			if (buttons[0].getGlobalBounds().contains(static_cast<Vector2f>(mousePos))) {
				currentMenu = MenuType::VOLUME;
				buttons.clear();
				initVolumeMenu();
			}
			else if (buttons[2].getGlobalBounds().contains(static_cast<Vector2f>(mousePos))) {
				return 2;
			}
		}

	}
	else if (currentMenu == MenuType::VOLUME) {
		if (event.type == Event::MouseButtonPressed) {
			if (buttons[2].getGlobalBounds().contains(static_cast<Vector2f>(mousePos))) {
				currentMenu = MenuType::OPTIONS;
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

 	/*if (event.type == Event::MouseButtonPressed) {
		if (volumeMusicSlider.getGlobalBounds().contains(static_cast<Vector2f>(mousePos)) ||
			volumeMusicBar.getGlobalBounds().contains(static_cast<Vector2f>(mousePos))) {
			isDragging = true;
			updateMusicVolume(mousePos);
		}

		for (size_t i = 0; i < buttons.size(); i++) {
			if (buttons[i].getGlobalBounds().contains(static_cast<Vector2f>(mousePos))) {
				resetCooldown();
				if (i == 2) { 
					return 2;
				}
			}
		}
	}*/

	return -1;
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
	
}


