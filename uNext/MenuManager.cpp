#include "MenuManager.h"
#include "Core.h"

/* ******************************************** */

MenuManager::MenuManager(void) {
	this->currentGameState = eMainMenu;

	this->oMainMenu = new MainMenu();
	this->oLoadingMenu = new LoadingMenu();
	this->oAboutMenu = new AboutMenu();
	//this->oConsole = new Console();
	this->oOptionsMenu = new OptionsMenu();
	//this->oLE = new LevelEditor();
	this->oPauseMenu = new PauseMenu();
}


MenuManager::~MenuManager(void) {
	delete activeOption;
	delete oMainMenu;
	delete oLoadingMenu;
	delete oAboutMenu;
}

/* ******************************************** */

void MenuManager::Update() {
	switch(currentGameState) {
		case eMainMenu:
			oMainMenu->Update();
			CCore::getMap()->UpdateBlocks();
			break;
		case eGameLoading:
			oLoadingMenu->Update();
			break;
		case eGame:
			CCore::getMap()->Update();
			CCore::getMap()->UpdateMinionsCollisions();
			//oLE->Update();
			break;
		case eAbout:
			CCore::getMap()->UpdateMinions();
			CCore::getMap()->UpdateMinionBlokcs();
			CCore::getMap()->UpdateBlocks();
			oAboutMenu->Update();
			break;
		case eOptions:
			oOptionsMenu->Update();
			break;
		case ePasue:
			oPauseMenu->Update();
			break;
	}
}

void MenuManager::Draw(sf::RenderWindow* rR) {
	switch(currentGameState) {
		case eMainMenu:
			CCore::getMap()->DrawMap(rR);
			CCore::getMap()->getPlayer()->Draw(rR);
			CCore::getMap()->DrawGameLayout(rR);
			oMainMenu->Draw(rR);
			break;
		case eGameLoading:
			oLoadingMenu->Draw(rR);
			break;
		case eGame:
			CCore::getMap()->Draw(rR);
			//oLE->Draw(rR);
			break;
		case eAbout:
			CCore::getMap()->DrawMap(rR);
			//CCore::getMap()->getPlayer()->Draw(rR);
			CCore::getMap()->DrawMinions(rR);
			oAboutMenu->Draw(rR);
			break;
		case eOptions:
			CCore::getMap()->DrawMap(rR);
			CCore::getMap()->DrawMinions(rR);
			CCore::getMap()->getPlayer()->Draw(rR);
			CCore::getMap()->DrawGameLayout(rR);
			oOptionsMenu->Draw(rR);
			break;
		case ePasue:
			CCore::getMap()->DrawMap(rR);
			CCore::getMap()->DrawMinions(rR);
			CCore::getMap()->getPlayer()->Draw(rR);
			CCore::getMap()->DrawGameLayout(rR);
			oPauseMenu->Draw(rR);
			break;
	}
	/* -- CRT EFFECT
	for(int i = 0; i < CCFG::GAME_WIDTH; i += 2) {
	}
	for(int i = 0; i < CCFG::GAME_HEIGHT; i += 2) {
	}*/

	//oConsole->Draw(rR);
}

void MenuManager::setBackgroundColor(sf::RenderWindow* rR) {
	// This method is kept for compatibility but not needed in SFML
	// Background color is now retrieved via getBackgroundColor()
}

sf::Color MenuManager::getBackgroundColor() {
	// For now, return black - proper color handling will be fixed later
	// TODO: Get actual color from Map or About menu
	return sf::Color(0, 0, 0);
}

/* ******************************************** */

void MenuManager::enter() {
	switch(currentGameState) {
		case eMainMenu:
			oMainMenu->enter();
			break;
		case eGame:
			CCore::getMap()->setDrawLines(!CCore::getMap()->getDrawLines());
			break;
		case eAbout:
			oAboutMenu->enter();
			break;
		case eOptions:
			oOptionsMenu->enter();
			break;
		case ePasue:
			oPauseMenu->enter();
			break;
	}
}

void MenuManager::escape() {
	switch(currentGameState) {
		case eGame:
			
			break;
		case eAbout:
			oAboutMenu->enter();
			break;
		case eOptions:
			oOptionsMenu->escape();
			break;
		case ePasue:
			oPauseMenu->escape();
			break;
		case eMainMenu:
			oMainMenu->escape();
			break;
	}
}

void MenuManager::setKey(int keyID) {
	switch(currentGameState) {
		case eOptions:
			oOptionsMenu->setKey(keyID);
			break;
	}
}

void MenuManager::keyPressed(int iDir) {
	switch(currentGameState) {
		case eMainMenu:
			oMainMenu->updateActiveButton(iDir);
			break;
		case eOptions:
			oOptionsMenu->updateActiveButton(iDir);
			break;
		case ePasue:
			oPauseMenu->updateActiveButton(iDir);
			break;
	}
}

void MenuManager::resetActiveOptionID(gameState ID) {
	switch(ID) {
		case eMainMenu:
			oMainMenu->activeMenuOption = 0;
			break;
		case eOptions:
			oOptionsMenu->activeMenuOption = 0;
			break;
		case ePasue:
			oPauseMenu->activeMenuOption = 0;
			break;
	}
}

/* ******************************************** */

int MenuManager::getViewID() {
	return currentGameState;
}

void MenuManager::setViewID(gameState viewID) {
	this->currentGameState = viewID;
}

CIMG* MenuManager::getActiveOption() {
	return activeOption;
}

void MenuManager::setActiveOption(sf::RenderWindow* rR) {
	activeOption = new CIMG("active_option", rR);
}

LoadingMenu* MenuManager::getLoadingMenu() {
	return oLoadingMenu;
}

AboutMenu* MenuManager::getAboutMenu() {
	return oAboutMenu;
}
/*
Console* MenuManager::getConsole() {
	return oConsole;
}

LevelEditor* MenuManager::getLE() {
	return oLE;
}
*/
OptionsMenu* MenuManager::getOptions() {
	return oOptionsMenu;
}