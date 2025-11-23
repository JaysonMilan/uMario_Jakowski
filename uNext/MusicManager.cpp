/************************
 * @author Łukasz Jakowski
 * @since  02.05.2014 16:13
 *
 ************************/

#include "MusicManager.h"

/* ******************************************** */

MusicManager::MusicManager(void) {



}

MusicManager::~MusicManager(void) {
	for(unsigned int i = 0; i < vMusic.size(); i++) {
		delete vMusic[i];
	}
	vMusic.clear();
}

/* ******************************************** */

void MusicManager::PlayMusic() {
	vMusic.push_back(loadMusic("overworld"));
	vMusic.push_back(loadMusic("overworld"));
	if(vMusic.size() > 0 && vMusic[0] != nullptr) {
		vMusic[0]->setVolume(100);
		vMusic[0]->setLoop(true);
		vMusic[0]->play();
	}
}

/* ******************************************** */

sf::Music* MusicManager::loadMusic(std::string fileName) {
	fileName = "files/sounds/" + fileName + ".wav";
	sf::Music* music = new sf::Music();
	if(!music->openFromFile(fileName)) {
		delete music;
		return nullptr;
	}
	return music;
}

/* ******************************************** */
