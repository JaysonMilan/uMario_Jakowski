#include "MainMenu.h"
#include "CFG.h"
#include "Core.h"

/* ******************************************** */

MainMenu::MainMenu(void) {
	this->lMO.push_back(new MenuOption("1 PLAYER GAME", 178, 276));
	this->lMO.push_back(new MenuOption("OPTIONS", 222, 308));
	this->lMO.push_back(new MenuOption("ABOUT", 237, 340));

	this->numOfMenuOptions = lMO.size();

	this->selectWorld = false;

	rSelectWorld.left = 122;
	rSelectWorld.top = 280;
	rSelectWorld.width = 306;
	rSelectWorld.height = 72;

	this->activeWorldID = this->activeSecondWorldID = 0;
}

MainMenu::~MainMenu(void) {

}

/* ******************************************** */

void MainMenu::Update() {
	CCFG::getMusic()->StopMusic();
	
	Menu::Update();
}

void MainMenu::Draw(sf::RenderWindow* rR) {
	CCFG::getSMBLOGO()->Draw(rR, 80, 48);
	Menu::Draw(rR);
	CCFG::getText()->Draw(rR, "WWW.LUKASZJAKOWSKI.PL", 4, CCFG::GAME_HEIGHT - 4 - 8, 8, 0, 0, 0);
	CCFG::getText()->Draw(rR, "WWW.LUKASZJAKOWSKI.PL", 5, CCFG::GAME_HEIGHT - 5 - 8, 8, 255, 255, 255);

	if(selectWorld) {
		rSelectWorld.left += 1;
		rSelectWorld.top += 1;
		rSelectWorld.height -= 2;
		rSelectWorld.width -= 2;
		rSelectWorld.left -= 1;
		rSelectWorld.top -= 1;
		rSelectWorld.height += 2;
		rSelectWorld.width += 2;

		CCFG::getText()->Draw(rR, "SELECT WORLD", rSelectWorld.left + rSelectWorld.width/2 - CCFG::getText()->getTextWidth("SELECT WORLD")/2, rSelectWorld.top + 16, 16, 255, 255, 255);

		for(int i = 0, extraX = 0; i < 8; i++) {
			if(i == activeWorldID) {
				CCFG::getText()->Draw(rR, std::to_string(i + 1) + "-" + std::to_string(activeSecondWorldID + 1), rSelectWorld.left + 16*(i + 1) + 16*i + extraX, rSelectWorld.top + 16 + 24, 16, 255, 255, 255);

				extraX = 32;

				/*for(int j = 0; j < 4; j++) {
					if(j == activeSecondWorldID) {
						CCFG::getText()->Draw(rR, std::to_string(j + 1), rSelectWorld.left + 16*(i + 1) + 16*i, rSelectWorld.top + 40 + 24*j, 16, 255, 255, 255);
					} else {
						CCFG::getText()->Draw(rR, std::to_string(j + 1), rSelectWorld.left + 16*(i + 1) + 16*i, rSelectWorld.top + 40 + 24*j, 16, 90, 90, 90);
					}
				}*/
			} else {
				CCFG::getText()->Draw(rR, std::to_string(i + 1), rSelectWorld.left + 16*(i + 1) + 16*i + extraX, rSelectWorld.top + 16 + 24, 16, 90, 90, 90);
			}
		}

		CCore::getMap()->setBackgroundColor(rR);
	}
}

/* ******************************************** */

void MainMenu::enter() {
	switch(activeMenuOption) {
		case 0:
			if(!selectWorld) {
				selectWorld = true;
			} else {
				CCFG::getMM()->getLoadingMenu()->updateTime();
				CCore::getMap()->resetGameData();
				CCore::getMap()->setCurrentLevelID(activeWorldID * 4 + activeSecondWorldID);
				CCFG::getMM()->setViewID(CCFG::getMM()->eGameLoading);
				CCFG::getMM()->getLoadingMenu()->loadingType = true;
				CCore::getMap()->setSpawnPointID(0);
				selectWorld = false;
			}
			break;
		case 1:
			CCFG::getMM()->getOptions()->setEscapeToMainMenu(true);
			CCFG::getMM()->resetActiveOptionID(CCFG::getMM()->eOptions);
			CCFG::getMM()->getOptions()->updateVolumeRect();
			CCFG::getMM()->setViewID(CCFG::getMM()->eOptions);
			break;
		case 2:
			CCFG::getMM()->getAboutMenu()->updateTime();
			CCFG::getMM()->setViewID(CCFG::getMM()->eAbout);
			CCFG::getMusic()->PlayMusic(CCFG::getMusic()->mOVERWORLD);
			break;
	}
}

void MainMenu::escape() {
	selectWorld = false;
}

void MainMenu::updateActiveButton(int iDir) {
	switch(iDir) {
		case 0: case 2:
			if(!selectWorld) {
				Menu::updateActiveButton(iDir);
			} else {
				switch(iDir) {
					case 0:
						if(activeSecondWorldID < 1) {
							activeSecondWorldID = 3;
						} else {
							--activeSecondWorldID;
						}
						break;
					case 2:
						if(activeSecondWorldID > 2) {
							activeSecondWorldID = 0;
						} else {
							++activeSecondWorldID;
						}
						break;
				}
			}
			break;
		case 1:
			if(selectWorld) {
				if(activeWorldID < 7) {
					++activeWorldID;
				} else {
					activeWorldID = 0;
				}
			}
			break;
		case 3:
			if(selectWorld) {
				if(activeWorldID > 0) {
					--activeWorldID;
				} else {
					activeWorldID = 7;
				}
			}
			break;
	}
}