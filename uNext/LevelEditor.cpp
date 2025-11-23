#include "LevelEditor.h"
#include "CFG.h"
#include "Core.h"

/* ******************************************** */

LevelEditor::LevelEditor(void) {
	this->rBlock.height = this->rBlock.width = 32;
	this->currentBlockID = 0;
}

LevelEditor::~LevelEditor(void) {

}

/* ******************************************** */

void LevelEditor::Update() {
	if(CCore::mouseRightPressed) {
		rDrag.width = CCore::mouseX - rDrag.left;
		rDrag.height = CCore::mouseY - rDrag.top;
	} else {
		rBlock.left = CCore::mouseX - (-(int)CCore::getMap()->getXPos() + CCore::mouseX)%32;
		rBlock.top = CCore::mouseY - (CCore::mouseY - 16)%32;
		rBlock.width = rBlock.height = 32;

		rDrag.left = CCore::mouseX;
		rDrag.top = CCore::mouseY;
	}

	editMap();
}

void LevelEditor::Draw(sf::RenderWindow* rR) {
	
	if(CCore::mouseRightPressed) {
		drawStruct(rR);

	} else {
		CCore::getMap()->getBlock(currentBlockID)->getSprite()->getTexture()->Draw(rR, rBlock.left, rBlock.top);
	}

}

/* ******************************************** */

void LevelEditor::mouseWheel(int Y) {
	if(Y > 0) {
		if(currentBlockID > 0) {
			currentBlockID -= Y;
		}
	} else {
		if(currentBlockID < 100) {
			currentBlockID -= Y;
		}
	}
}

void LevelEditor::editMap() {
	if(CCore::mouseLeftPressed) {
		CCore::getMap()->getMapBlock((int)(((-CCore::getMap()->getXPos() + CCore::mouseX) - (int)((-CCore::getMap()->getXPos() + CCore::mouseX))%32)/32), (CCFG::GAME_HEIGHT - CCore::mouseY + 16)/32)->setBlockID(currentBlockID);
	}
}

/* ******************************************** */

void LevelEditor::drawStruct(sf::RenderWindow* rR) {
	int W = CCore::mouseX - CCore::mouseX%32 - rDrag.left + rDrag.left%32;
	int H = CCore::mouseY - (CCore::mouseY - 16)%32 - rDrag.top + rDrag.top%32;
	W += W > 0 ? 32 : 0;
	H += H > 0 ? 32 : -32;

	for(int i = 0, k = 0; k < (W > 0 ? W : -W); k += 32, i += W > 0 ? 32 : -32) {
		for(int j = 0, m = 0; m < (H > 0 ? H : -H); m += 32, j += H > 0 ? 32 : -32) {
			CCore::getMap()->getBlock(currentBlockID)->getSprite()->getTexture()->Draw(rR, rBlock.left + i, rBlock.top + j);
		}
	}
}