#include "CFG.h"

/* ******************************************** */

CCFG::CCFG(void) { }

CCFG::~CCFG(void) {
	delete oText;
	delete oMM;
	delete tSMBLOGO;
}

/* ******************************************** */

int CCFG::GAME_WIDTH  = 800;
int CCFG::GAME_HEIGHT = 448;

Text* CCFG::oText = new Text();
CIMG* CCFG::tSMBLOGO = new CIMG();

MenuManager* CCFG::oMM = new MenuManager();
Music* CCFG::oMusic = new Music();
sf::Clock* CCFG::gameClock = new sf::Clock();

bool CCFG::keySpace = false;

int CCFG::keyIDA = 0;
int CCFG::keyIDD = 0;
int CCFG::keyIDS = 0;
int CCFG::keyIDSpace = 0;
int CCFG::keyIDShift = 0;

bool CCFG::canMoveBackward = true;

/* ******************************************** */

Text* CCFG::getText() {
	return oText;
}

MenuManager* CCFG::getMM() {
	return oMM;
}

Music* CCFG::getMusic() {
	return oMusic;
}

CIMG* CCFG::getSMBLOGO() {
	return tSMBLOGO;
}

unsigned long CCFG::getTicks() {
	return gameClock->getElapsedTime().asMilliseconds();
}

std::string CCFG::getKeyString(int keyID) {
	if(keyID >= 97 && keyID <= 122) {
		return std::string(1, '0' + (keyID - 32) - 48);
	}

	if(keyID >= 48 && keyID <= 57) {
		return std::string(1, '0' + (keyID - 32) - 48);
	}

	switch(keyID) {
		case sf::Keyboard::Escape:
			return "ESCAPE";
		case sf::Keyboard::Space:
			return "SPACE";
		case sf::Keyboard::LShift:
			return "LSHIFT";
		case sf::Keyboard::RShift:
			return "RSHIFT";
		case sf::Keyboard::Up:
			return "UP";
		case sf::Keyboard::Down:
			return "DOWN";
		case sf::Keyboard::Right:
			return "RIGHT";
		case sf::Keyboard::Left:
			return "LEFT";
		case sf::Keyboard::LControl:
			return "LCTRL";
		case sf::Keyboard::RControl:
			return "RCTRL";
	}

	return "NONE";
}