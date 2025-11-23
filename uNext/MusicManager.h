#pragma once

#ifndef MUSICMANAGER_H
#define MUSICMANAGER_H	

#include <SFML/Audio.hpp>
#include <string>
#include <vector>

class MusicManager
{
private:
	std::vector<sf::Music*> vMusic;

	std::vector<sf::SoundBuffer*> vChunkBuffers;
	std::vector<sf::Sound*> vChunk;
public:
	MusicManager(void);
	~MusicManager(void);

	sf::Music* loadMusic(std::string fileName);

	void PlayMusic();

};

#endif