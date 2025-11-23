#include "header.h"
#include "Core.h"
#include "IMG.h"
#include "CFG.h"
#include "Text.h"

/* ******************************************** */

Map* CCore::oMap = new Map();
bool CCore::mouseLeftPressed = false;
bool CCore::mouseRightPressed = false;
int CCore::mouseX = 0;
int CCore::mouseY = 0;
bool CCore::quitGame = false;

bool CCore::movePressed = false;
bool CCore::keyMenuPressed = false;
bool CCore::keyS = false;
bool CCore::keyW = false;
bool CCore::keyA = false;
bool CCore::keyD = false;
bool CCore::keyShift = false;
bool CCore::keyAPressed = false;
bool CCore::keyDPressed = false;

CCore::CCore(void) {
	this->quitGame = false;
	this->iFPS = 0;
	this->iNumOfFPS = 0;
	this->lFPSTime = 0;

	window = new sf::RenderWindow(sf::VideoMode(CCFG::GAME_WIDTH, CCFG::GAME_HEIGHT), "uMario - www.LukaszJakowski.pl");

	if(!window) {
		quitGame = true;
	}

	// ----- ICO
	std::string fileName = "files/images/ico.bmp";
	sf::Image icon;
	if(icon.loadFromFile(fileName)) {
		icon.createMaskFromColor(sf::Color(255, 0, 255));
		window->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
	}

	mainEvent = new sf::Event();
	// ----- ICO

	oMap = new Map(window);
	CCFG::getMM()->setActiveOption(window);
	CCFG::getSMBLOGO()->setIMG("super_mario_bros", window);

	CCFG::getMusic()->PlayMusic();

	this->keyMenuPressed = this->movePressed = this->keyS = this->keyW = this->keyA = this->keyD = this->keyShift = false;

	this->keyAPressed = this->keyDPressed = this->firstDir = false;

	this->mouseX = this->mouseY = 0;

	CCFG::keyIDA = sf::Keyboard::A;
	CCFG::keyIDS = sf::Keyboard::S;
	CCFG::keyIDD = sf::Keyboard::D;
	CCFG::keyIDSpace = sf::Keyboard::Space;
	CCFG::keyIDShift = sf::Keyboard::LShift;
}

CCore::~CCore(void) {
	delete oMap;
	delete mainEvent;
	delete window;
}

/* ******************************************** */

void CCore::mainLoop() {
	sf::Clock fpsClock;
	lFPSTime = fpsClock.getElapsedTime().asMilliseconds();

	while(!quitGame && window->isOpen()) {
		sf::Clock frameClock;

		while(window->pollEvent(*mainEvent)) {
			if(mainEvent->type == sf::Event::Closed) {
				quitGame = true;
				window->close();
			}
			Input();
			MouseInput();
		}

		window->clear(CCFG::getMM()->getBackgroundColor());

		Update();
		Draw();

		/*CCFG::getText()->Draw(window, "FPS:" + std::to_string(iNumOfFPS), CCFG::GAME_WIDTH - CCFG::getText()->getTextWidth("FPS:" + std::to_string(iNumOfFPS), 8) - 8, 5, 8);

		if(fpsClock.getElapsedTime().asMilliseconds() - 1000 >= lFPSTime) {
			lFPSTime = fpsClock.getElapsedTime().asMilliseconds();
			iNumOfFPS = iFPS;
			iFPS = 0;
		}

		++iFPS;*/

		window->display();

		long elapsed = frameClock.getElapsedTime().asMilliseconds();
		if(elapsed < MIN_FRAME_TIME) {
			sf::sleep(sf::milliseconds(MIN_FRAME_TIME - elapsed));
		}
	}
}

void CCore::Input() {
	switch(CCFG::getMM()->getViewID()) {
		case 2: case 7:
			if(!oMap->getInEvent()) {
				InputPlayer();
			} else {
				resetMove();
			}
			break;
		default:
			InputMenu();
			break;
	}
}

void CCore::InputMenu() {
	if(mainEvent->type == sf::Event::KeyPressed) {
		CCFG::getMM()->setKey(mainEvent->key.code);

		switch(mainEvent->key.code) {
			case sf::Keyboard::S: case sf::Keyboard::Down:
				if(!keyMenuPressed) {
					CCFG::getMM()->keyPressed(2);
					keyMenuPressed = true;
				}
				break;
			case sf::Keyboard::W: case sf::Keyboard::Up:
				if(!keyMenuPressed) {
					CCFG::getMM()->keyPressed(0);
					keyMenuPressed = true;
				}
				break;
			case sf::Keyboard::Enter:
				if(!keyMenuPressed) {
					CCFG::getMM()->enter();
					keyMenuPressed = true;
				}
				break;
			case sf::Keyboard::Escape:
				if(!keyMenuPressed) {
					CCFG::getMM()->escape();
					keyMenuPressed = true;
				}
				break;
			case sf::Keyboard::Left: case sf::Keyboard::D:
				if(!keyMenuPressed) {
					CCFG::getMM()->keyPressed(3);
					keyMenuPressed = true;
				}
				break;
			case sf::Keyboard::Right: case sf::Keyboard::A:
				if(!keyMenuPressed) {
					CCFG::getMM()->keyPressed(1);
					keyMenuPressed = true;
				}
				break;
			default:
				break;
		}
	}

	if(mainEvent->type == sf::Event::KeyReleased) {
		switch(mainEvent->key.code) {
			case sf::Keyboard::S: case sf::Keyboard::Down: case sf::Keyboard::W: case sf::Keyboard::Up:
			case sf::Keyboard::Enter: case sf::Keyboard::Escape: case sf::Keyboard::A: case sf::Keyboard::Right:
			case sf::Keyboard::Left: case sf::Keyboard::D:
				keyMenuPressed = false;
				break;
			default:
				break;
		}
	}
}

void CCore::InputPlayer() {
	if(mainEvent->type == sf::Event::LostFocus) {
		CCFG::getMM()->resetActiveOptionID(CCFG::getMM()->ePasue);
		CCFG::getMM()->setViewID(CCFG::getMM()->ePasue);
		CCFG::getMusic()->PlayChunk(CCFG::getMusic()->cPASUE);
		CCFG::getMusic()->PauseMusic();
	}

	if(mainEvent->type == sf::Event::KeyReleased) {
		if(mainEvent->key.code == CCFG::keyIDD) {
			if(firstDir) {
				firstDir = false;
			}

			keyDPressed = false;
		}

		if(mainEvent->key.code == CCFG::keyIDS) {
			oMap->getPlayer()->setSquat(false);
			keyS = false;
		}

		if(mainEvent->key.code == CCFG::keyIDA) {
			if(!firstDir) {
				firstDir = true;
			}

			keyAPressed = false;
		}

		if(mainEvent->key.code == CCFG::keyIDSpace) {
			CCFG::keySpace = false;
		}

		if(mainEvent->key.code == CCFG::keyIDShift) {
			if(keyShift) {
				oMap->getPlayer()->resetRun();
				keyShift = false;
			}
		}

		switch(mainEvent->key.code) {
			case sf::Keyboard::Enter: case sf::Keyboard::Escape:
				keyMenuPressed = false;
				break;
			default:
				break;
		}
	}

	if(mainEvent->type == sf::Event::KeyPressed) {
		if(mainEvent->key.code == CCFG::keyIDD) {
			keyDPressed = true;
			if(!keyAPressed) {
				firstDir = true;
			}
		}

		if(mainEvent->key.code == CCFG::keyIDS) {
			if(!keyS) {
				keyS = true;
				if(!oMap->getUnderWater() && !oMap->getPlayer()->getInLevelAnimation()) oMap->getPlayer()->setSquat(true);
			}
		}

		if(mainEvent->key.code == CCFG::keyIDA) {
			keyAPressed = true;
			if(!keyDPressed) {
				firstDir = false;
			}
		}

		if(mainEvent->key.code == CCFG::keyIDSpace) {
			if(!CCFG::keySpace) {
				oMap->getPlayer()->jump();
				CCFG::keySpace = true;
			}
		}

		if(mainEvent->key.code == CCFG::keyIDShift) {
			if(!keyShift) {
				oMap->getPlayer()->startRun();
				keyShift = true;
			}
		}

		switch(mainEvent->key.code) {
			case sf::Keyboard::Enter:
				if(!keyMenuPressed) {
					CCFG::getMM()->enter();
					keyMenuPressed = true;
				}
				break;
			case sf::Keyboard::Escape:
				if(!keyMenuPressed && CCFG::getMM()->getViewID() == CCFG::getMM()->eGame) {
					CCFG::getMM()->resetActiveOptionID(CCFG::getMM()->ePasue);
					CCFG::getMM()->setViewID(CCFG::getMM()->ePasue);
					CCFG::getMusic()->PlayChunk(CCFG::getMusic()->cPASUE);
					CCFG::getMusic()->PauseMusic();
					keyMenuPressed = true;
				}
				break;
			default:
				break;
		}
	}

	if(keyAPressed) {
		if(!oMap->getPlayer()->getMove() && firstDir == false && !oMap->getPlayer()->getChangeMoveDirection() && !oMap->getPlayer()->getSquat()) {
			oMap->getPlayer()->startMove();
			oMap->getPlayer()->setMoveDirection(false);
		} else if(!keyDPressed && oMap->getPlayer()->getMoveSpeed() > 0 && firstDir != oMap->getPlayer()->getMoveDirection()) {
			oMap->getPlayer()->setChangeMoveDirection();
		}
	}

	if(keyDPressed) {
		if(!oMap->getPlayer()->getMove() && firstDir == true && !oMap->getPlayer()->getChangeMoveDirection() && !oMap->getPlayer()->getSquat()) {
			oMap->getPlayer()->startMove();
			oMap->getPlayer()->setMoveDirection(true);
		} else if(!keyAPressed && oMap->getPlayer()->getMoveSpeed() > 0 && firstDir != oMap->getPlayer()->getMoveDirection()) {
			oMap->getPlayer()->setChangeMoveDirection();
		}
	}

	if(oMap->getPlayer()->getMove() && !keyAPressed && !keyDPressed) {
		oMap->getPlayer()->resetMove();
	}
}

void CCore::MouseInput() {
	switch(mainEvent->type) {
		case sf::Event::MouseButtonPressed: {
			switch (mainEvent->mouseButton.button) {
				case sf::Mouse::Left:
					mouseLeftPressed = true;
					break;
				case sf::Mouse::Right:
					mouseRightPressed = true;
					break;
				default:
					break;
			}
			break;
		}
		case sf::Event::MouseMoved: {
			mouseX = mainEvent->mouseMove.x;
			mouseY = mainEvent->mouseMove.y;
			//CCFG::getMM()->getConsole()->print("x:" + std::to_string(mouseX));
			//CCFG::getMM()->getConsole()->print("y:" + std::to_string(mouseY));
			break;
		}
		case sf::Event::MouseButtonReleased: {
			switch (mainEvent->mouseButton.button) {
				case sf::Mouse::Left:
					mouseLeftPressed = false;
					break;
				case sf::Mouse::Right:
					mouseRightPressed = false;
					break;
				default:
					break;
			}
			break;
		}
		case sf::Event::MouseWheelScrolled:
			//CCFG::getMM()->getLE()->mouseWheel(mainEvent->mouseWheelScroll.delta);
			break;
		default:
			break;
	}
}

void CCore::resetKeys() {
	movePressed = keyMenuPressed = keyS = keyW = keyA = keyD = CCFG::keySpace = keyShift = keyAPressed = keyDPressed = false;
}

void CCore::Update() {
	CCFG::getMM()->Update();
}


void CCore::Draw() {
	CCFG::getMM()->Draw(window);
}

/* ******************************************** */

void CCore::resetMove() {
	this->keyAPressed = this->keyDPressed = false;
}

Map* CCore::getMap() {
	return oMap;
}
