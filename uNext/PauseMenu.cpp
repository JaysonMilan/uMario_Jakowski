#include "PauseMenu.h"
#include "CFG.h"
#include "Core.h"

/* ******************************************** */

PauseMenu::PauseMenu(void) {
	rPause.left = 220;
	rPause.top = 140;
	rPause.width = 360;
	rPause.height = 142;

	this->lMO.push_back(new MenuOption("RESUME", 0, 156));
	this->lMO.push_back(new MenuOption("OPTIONS", 0, 180));

	this->lMO.push_back(new MenuOption("QUIT TO MENU", 0, 228));
	this->lMO.push_back(new MenuOption("QUIT TO DESKTOP", 0, 252));

	this->numOfMenuOptions = lMO.size();
}

PauseMenu::~PauseMenu(void) {

}

/* ******************************************** */

void PauseMenu::Update() {

}

void PauseMenu::Draw(sf::RenderWindow* rR) {
	rPause.left += 1;
	rPause.top += 1;
	rPause.height -= 2;
	rPause.width -= 2;
	rPause.left -= 1;
	rPause.top -= 1;
	rPause.height += 2;
	rPause.width += 2;

	for(unsigned int i = 0; i < lMO.size(); i++) {
		if(i == activeMenuOption) {
			CCFG::getText()->DrawCenterX(rR, lMO[i]->getText(), lMO[i]->getYPos(), 16, 255, 255, 255);
		} else {
			CCFG::getText()->DrawCenterX(rR, lMO[i]->getText(), lMO[i]->getYPos(), 16, 90, 90, 90);
		}
	}

	CCore::getMap()->setBackgroundColor(rR);
}

/* ******************************************** */

void PauseMenu::enter() {
	switch(activeMenuOption) {
		case 0:
			CCFG::getMM()->setViewID(CCFG::getMM()->eGame);
			CCFG::getMusic()->PlayMusic();
			break;
		case 1:
			CCFG::getMM()->getOptions()->setEscapeToMainMenu(false);
			CCFG::getMM()->resetActiveOptionID(CCFG::getMM()->eOptions);
			CCFG::getMM()->getOptions()->updateVolumeRect();
			CCFG::getMM()->setViewID(CCFG::getMM()->eOptions);
			break;
		case 2:
			CCore::getMap()->resetGameData();
			CCFG::getMM()->setViewID(CCFG::getMM()->eMainMenu);
			break;
		case 3:
			CCore::quitGame = true;
			break;
	}
}

void PauseMenu::escape() {
	CCFG::getMM()->setViewID(CCFG::getMM()->eGame);
	CCFG::getMusic()->PauseMusic();
}

void PauseMenu::updateActiveButton(int iDir) {
	Menu::updateActiveButton(iDir);
}