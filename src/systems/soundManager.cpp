#include "SoundManager.hpp"
#include <iostream>
SoundManager::SoundManager() : currentMusic(nullptr), musicVolume(50.f), soundVolume(50.f) {}

SoundManager::~SoundManager() {}

void SoundManager::loadMusic(const std::string& name, const std::string& filepath)
{
	auto music = std::make_unique<sf::Music>();
	if (!music->openFromFile(filepath)) {
		std::cerr << "Erreur, impossible de charger la musique " << filepath << std::endl;
		return;
	}
	musicTracks[name] = std::move(music);
}

void SoundManager::playMusic(const std::string& name, bool loop)
{
	if (musicTracks.find(name) == musicTracks.end()) {
		std::cerr << "Erreur : Musique " << name << " non chargée" << std::endl;
		return;
	}

	if (currentMusic) {
		currentMusic->stop();
	}

	currentMusic = musicTracks[name].get();
	currentMusic->setLoop(loop);
	currentMusic->setVolume(musicVolume);
	currentMusic->play();
}

void SoundManager::stopMusic()
{
	if (currentMusic) {
		currentMusic->stop();
	}
}

void SoundManager::setMusicVolume(float volume)
{
	musicVolume = volume;
	if (currentMusic) {
		currentMusic->setVolume(volume);
	}
}

void SoundManager::loadSound(const std::string& name, const std::string& filepath)
{
	sf::SoundBuffer buffer;
	if (!buffer.loadFromFile(filepath)) {
		std::cerr << "Erreur : Impossible de charger le son" << filepath << std::endl;
		return;
	}
	soundBuffers[name] = buffer;
	soundEffects[name].setBuffer(soundBuffers[name]);
}

void SoundManager::playSound(const std::string name)
{
	if (soundEffects.find(name) == soundEffects.end()) {
		std::cerr << "Erreur : Son " << name << " non chargé" << std::endl;
	}

	soundEffects[name].setVolume(soundVolume);
	soundEffects[name].play();
}

void SoundManager::setSoundVolume(float volume)
{
	soundVolume = volume;
}

