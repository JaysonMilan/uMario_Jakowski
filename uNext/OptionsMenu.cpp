#include "OptionsMenu.h"
#include "CFG.h"
#include "Core.h"

/* ******************************************** */

OptionsMenu::OptionsMenu(void) {
	rRect.left = 58;
	rRect.top = 48;
	rRect.width = 403;
	rRect.height = 324;

	this->lMO.push_back(new MenuOption("VOLUME", 73, 65));
	this->lMO.push_back(new MenuOption("LEFT", 73, 89));
	this->lMO.push_back(new MenuOption("DOWN", 73, 113));
	this->lMO.push_back(new MenuOption("RIGHT", 73, 137));
	this->lMO.push_back(new MenuOption("JUMP", 73, 161));
	this->lMO.push_back(new MenuOption("RUN", 73, 185));
	this->lMO.push_back(new MenuOption("CAN MOVE BACKWARD", 73, 209));
	this->lMO.push_back(new MenuOption("MAIN MENU", 73, 257));

	this->numOfMenuOptions = lMO.size();

	this->inSetKey = this->resetSetKey = false;

	rSetKeyRect.left = 75;
	rSetKeyRect.top = 284;
	rSetKeyRect.width = 369;
	rSetKeyRect.height = 71;

	rVolumeBG.left = 185;
	rVolumeBG.top = 65;
	rVolumeBG.height = 16;
	rVolumeBG.width = 200;

	rVolume.left = 185;
	rVolume.top = 65;
	rVolume.height = 16;
	rVolume.width = 100;

	this->escapeToMainMenu = true;
}

OptionsMenu::~OptionsMenu(void) {

}

/* ******************************************** */

void OptionsMenu::Update() {
	if(resetSetKey) {
		inSetKey = false;
		resetSetKey = false;
	}
}

void OptionsMenu::Draw(sf::RenderWindow* rR) {
	rRect.left += 1;
	rRect.top += 1;
	rRect.height -= 2;
	rRect.width -= 2;
	rRect.left -= 1;
	rRect.top -= 1;
	rRect.height += 2;
	rRect.width += 2;

	for(unsigned int i = 0; i < lMO.size(); i++) {
		if(i == activeMenuOption) {
			CCFG::getText()->Draw(rR, lMO[i]->getText(), lMO[i]->getXPos(), lMO[i]->getYPos(), 16, 255, 255, 255);
		} else {
			CCFG::getText()->Draw(rR, lMO[i]->getText(), lMO[i]->getXPos(), lMO[i]->getYPos(), 16, 90, 90, 90);
		}
	}



	if(activeMenuOption == 0) {
	} else {
	}

	CCFG::getText()->Draw(rR, CCFG::getKeyString(CCFG::keyIDA), 185, 89, 16, activeMenuOption == 1 ? 255 : 90, activeMenuOption == 1 ? 255 : 90, activeMenuOption == 1 ? 255 : 90);
	CCFG::getText()->Draw(rR, CCFG::getKeyString(CCFG::keyIDS), 185, 113, 16, activeMenuOption == 2 ? 255 : 90, activeMenuOption == 2 ? 255 : 90, activeMenuOption == 2 ? 255 : 90);
	CCFG::getText()->Draw(rR, CCFG::getKeyString(CCFG::keyIDD), 185, 137, 16, activeMenuOption == 3 ? 255 : 90, activeMenuOption == 3 ? 255 : 90, activeMenuOption == 3 ? 255 : 90);
	CCFG::getText()->Draw(rR, CCFG::getKeyString(CCFG::keyIDSpace), 185, 161, 16, activeMenuOption == 4 ? 255 : 90, activeMenuOption == 4 ? 255 : 90, activeMenuOption == 4 ? 255 : 90);
	CCFG::getText()->Draw(rR, CCFG::getKeyString(CCFG::keyIDShift), 185, 185, 16, activeMenuOption == 5 ? 255 : 90, activeMenuOption == 5 ? 255 : 90, activeMenuOption == 5 ? 255 : 90);

	CCFG::getText()->Draw(rR, CCFG::canMoveBackward ? "TRUE" : "FALSE", 357, 209, 16, activeMenuOption == 6 ? 255 : 90, activeMenuOption == 6 ? 255 : 90, activeMenuOption == 6 ? 255 : 90);

	if(inSetKey) {
		rSetKeyRect.left += 1;
		rSetKeyRect.top += 1;
		rSetKeyRect.height -= 2;
		rSetKeyRect.width -= 2;
		rSetKeyRect.left -= 1;
		rSetKeyRect.top -= 1;
		rSetKeyRect.height += 2;
		rSetKeyRect.width += 2;

		CCFG::getText()->Draw(rR, "PRESS KEY FOR " + lMO[activeMenuOption]->getText(), 92, rSetKeyRect.top + 16, 16, 255, 255, 255);
		CCFG::getText()->Draw(rR, "PRESS ESC TO CANCEL", 92, rSetKeyRect.top + 40, 16, 255, 255, 255);
	}

	CCore::getMap()->setBackgroundColor(rR);
}

/* ******************************************** */

void OptionsMenu::enter() {
	switch(activeMenuOption) {
		case 0:
			CCFG::getMusic()->PlayChunk(CCFG::getMusic()->cCOIN);
			break;
		case 1: case 2: case 3: case 4: case 5:
			inSetKey = true;
			break;
		case 6:
			CCFG::canMoveBackward = !CCFG::canMoveBackward;
			break;
		case 7:
			CCore::getMap()->resetGameData();
			CCFG::getMM()->setViewID(CCFG::getMM()->eMainMenu);
			break;
	}
}

void OptionsMenu::escape() {
	if(inSetKey) {
		resetSetKey = true;
	} else {
		if(escapeToMainMenu) {
			CCore::getMap()->resetGameData();
			CCFG::getMM()->setViewID(CCFG::getMM()->eMainMenu);
		} else {
			CCFG::getMM()->setViewID(CCFG::getMM()->ePasue);
		}
	}
}

void OptionsMenu::setKey(int keyID) {
	if(inSetKey && keyID != sf::Keyboard::Enter && keyID != sf::Keyboard::Enter && keyID != sf::Keyboard::Escape) {
		switch(activeMenuOption) {
			case 1:
				CCFG::keyIDA = keyID;
				if(CCFG::keyIDD == keyID) CCFG::keyIDD = 0;
				if(CCFG::keyIDS == keyID) CCFG::keyIDS = 0;
				if(CCFG::keyIDSpace == keyID) CCFG::keyIDSpace = 0;
				if(CCFG::keyIDShift == keyID) CCFG::keyIDShift = 0;
				break;
			case 2:
				CCFG::keyIDS = keyID;
				if(CCFG::keyIDA == keyID) CCFG::keyIDA = 0;
				if(CCFG::keyIDD == keyID) CCFG::keyIDD = 0;
				if(CCFG::keyIDSpace == keyID) CCFG::keyIDSpace = 0;
				if(CCFG::keyIDShift == keyID) CCFG::keyIDShift = 0;
				break;
			case 3:
				CCFG::keyIDD = keyID;
				if(CCFG::keyIDA == keyID) CCFG::keyIDA = 0;
				if(CCFG::keyIDS == keyID) CCFG::keyIDS = 0;
				if(CCFG::keyIDSpace == keyID) CCFG::keyIDSpace = 0;
				if(CCFG::keyIDShift == keyID) CCFG::keyIDShift = 0;
				break;
			case 4:
				CCFG::keyIDSpace = keyID;
				if(CCFG::keyIDA == keyID) CCFG::keyIDA = 0;
				if(CCFG::keyIDS == keyID) CCFG::keyIDS = 0;
				if(CCFG::keyIDD == keyID) CCFG::keyIDD = 0;
				if(CCFG::keyIDShift == keyID) CCFG::keyIDShift = 0;
				break;
			case 5:
				CCFG::keyIDShift = keyID;
				if(CCFG::keyIDA == keyID) CCFG::keyIDA = 0;
				if(CCFG::keyIDS == keyID) CCFG::keyIDS = 0;
				if(CCFG::keyIDD == keyID) CCFG::keyIDD = 0;
				if(CCFG::keyIDSpace == keyID) CCFG::keyIDSpace = 0;
				break;
		}
		resetSetKey = true;
	} else if(keyID == sf::Keyboard::Escape) {
		resetSetKey = true;
	}
}

void OptionsMenu::updateActiveButton(int iDir) {
	if(activeMenuOption == 0 && (iDir == 1 || iDir == 3)) {
		switch(iDir) {
			case 1:
				if(CCFG::getMusic()->getVolume() < 100) {
					CCFG::getMusic()->setVolume(CCFG::getMusic()->getVolume() + 5);
				} else {
					CCFG::getMusic()->setVolume(100);
				}
				break;
			case 3:
				if(CCFG::getMusic()->getVolume() > 0) {
					CCFG::getMusic()->setVolume(CCFG::getMusic()->getVolume() - 5);
				} else {
					CCFG::getMusic()->setVolume(0);
				}
				break;
		}
		updateVolumeRect();
		CCFG::getMusic()->PlayChunk(CCFG::getMusic()->cCOIN);
	}
	if(!inSetKey) {
		Menu::updateActiveButton(iDir);
	}
}

/* ******************************************** */

void OptionsMenu::updateVolumeRect() {
	rVolume.width = CCFG::getMusic()->getVolume()*2;
}

void OptionsMenu::setEscapeToMainMenu(bool escapeToMainMenu) {
	this->escapeToMainMenu = escapeToMainMenu;
}