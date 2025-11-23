#include "Text.h"
#include "CFG.h"

/* ******************************************** */

Text::Text(void) {
	rCrop.left = 0;
	rCrop.top = 0;
	rCrop.width = 8;
	rCrop.height = 8;

	rRect.left = 0;
	rRect.top = 0;
	rRect.width = 16;
	rRect.height = 16;

	this->fontSize = 16;
	this->extraLeft = 0;
	this->nextExtraLeft = 0;
}

Text::~Text(void) {
	delete FONT;
}

/* ******************************************** */

void Text::Draw(sf::RenderWindow* rR, std::string sText, int X, int Y, int fontSize) {
	this->fontSize = fontSize;
	this->extraLeft = 0;
	this->nextExtraLeft = 0;

	for(unsigned int i = 0; i < sText.size(); i++) {
		rCrop.left = getPos(sText.at(i));

		rRect.left = X + fontSize * i - extraLeft;
		rRect.top = Y;
		rRect.width = fontSize;
		rRect.height = fontSize;
		FONT->Draw(rR, rCrop, rRect);
		extraLeft += nextExtraLeft;
		nextExtraLeft = 0;
	}
}

void Text::Draw(sf::RenderWindow* rR, std::string sText, int X, int Y, int fontSize, int iR, int iG, int iB) {
	this->fontSize = fontSize;
	this->extraLeft = 0;
	this->nextExtraLeft = 0;

	for(unsigned int i = 0; i < sText.size(); i++) {
		// SFML color modulation is handled differently - would need to modify IMG class
		// For now, just draw normally
		rCrop.left = getPos(sText.at(i));

		rRect.left = X + fontSize * i - extraLeft;
		rRect.top = Y;
		rRect.width = fontSize;
		rRect.height = fontSize;
		FONT->Draw(rR, rCrop, rRect);
		extraLeft += nextExtraLeft;
		nextExtraLeft = 0;
	}
}

void Text::DrawCenterX(sf::RenderWindow* rR, std::string sText, int Y, int fontSize, int iR, int iG, int iB) {
	int X = CCFG::GAME_WIDTH / 2 - getTextWidth(sText, fontSize) / 2;

	Draw(rR, sText, X, Y, fontSize, iR, iG, iB);
}

void Text::Draw(sf::RenderWindow* rR, std::string sText, int X, int Y, int iWidth, int iHeight) {
	for(unsigned int i = 0; i < sText.size(); i++) {
		rCrop.left = getPos(sText.at(i));

		rRect.left = X + iWidth * i - extraLeft;
		rRect.top = Y;
		rRect.width = iWidth;
		rRect.height = iHeight;
		FONT->Draw(rR, rCrop, rRect);
	}
}


void Text::DrawWS(sf::RenderWindow* rR, std::string sText, int X, int Y,int iR, int iG, int iB, int fontSize) {
	this->fontSize = fontSize;
	this->extraLeft = 0;
	this->nextExtraLeft = 0;

	for(unsigned int i = 0; i < sText.size(); i++) {
		// Shadow pass
		rCrop.left = getPos(sText.at(i));

		rRect.left = X + fontSize * i - extraLeft - 1;
		rRect.top = Y + 1;
		rRect.width = fontSize;
		rRect.height = fontSize;
		FONT->Draw(rR, rCrop, rRect);

		// Main pass
		rRect.left = X + fontSize * i - extraLeft + 1;
		rRect.top = Y - 1;
		FONT->Draw(rR, rCrop, rRect);
		extraLeft += nextExtraLeft;
		nextExtraLeft = 0;
	}
}

/* ******************************************** */

int Text::getTextWidth(std::string sText, int fontSize) {
	int iOutput = sText.size() * fontSize;
	nextExtraLeft = 0;

	for(unsigned int i = 0; i < sText.size(); i++) {
		checkExtra(sText.at(i));
	}

	iOutput -= nextExtraLeft;

	return iOutput;
}

int Text::getPos(int iChar) {
	if(iChar >= 43 && iChar < 91) {
		checkExtra(iChar);
		return (iChar - 43) * rCrop.width + rCrop.width;
	}

	if(iChar >= 118 && iChar < 123) { // v w x y z
		return (iChar - 70) * rCrop.width + rCrop.width;
	}

	return 0;
}

/* ******************************************** */

void Text::checkExtra(int iChar) {
	switch(iChar) {
	case 44: case 46: case 58: case 59:
		nextExtraLeft += 4 * fontSize / rRect.width;
		break;
	}
}

/* ******************************************** */

void Text::setFont(sf::RenderWindow* rR, std::string fileName) {
	FONT = new CIMG(fileName, rR);
}
