#ifndef SOUNDMANAGER_HPP
#define SOUNDMANAGER_HPP

#include <SFML/Audio.hpp>
#include <unordered_map>
#include <string>
#include <memory>

class SoundManager {
private:
	std::unordered_map<std::string, std::unique_ptr<sf::Music>> musicTracks;
	std::unordered_map<std::string, sf::SoundBuffer> soundBuffers;
	std::unordered_map<std::string, sf::Sound> soundEffects;

	sf::Music* currentMusic;
	float musicVolume;
	float soundVolume;

public:
	SoundManager();
	~SoundManager();

	void loadMusic(const std::string& name, const std::string& filepath);
	void playMusic(const std::string& name, bool loop = true);
	void stopMusic();
	void setMusicVolume(float volume);

	void loadSound(const std::string& name, const std::string& path);
	void playSound(const std::string name);
	void setSoundVolume(float volume);


};


#endif