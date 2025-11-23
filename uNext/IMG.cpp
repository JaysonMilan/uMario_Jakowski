#include "IMG.h"

/* ******************************************** */

CIMG::CIMG(void) { }

CIMG::CIMG(std::string fileName, sf::RenderWindow* window) {
	setIMG(fileName, window);
}

CIMG::~CIMG(void) {
	// sf::Texture handles cleanup automatically
}

/* ******************************************** */

void CIMG::Draw(sf::RenderWindow* window, int iXOffset, int iYOffset) {
	sprite.setPosition(iXOffset, iYOffset);
	window->draw(sprite);
}

void CIMG::Draw(sf::RenderWindow* window, int iXOffset, int iYOffset, bool bRotate) {
	sprite.setPosition(iXOffset, iYOffset);

	if(!bRotate) {
		sprite.setRotation(0);
		sprite.setScale(1, 1);
	} else {
		sprite.setRotation(180);
		sprite.setScale(1, -1);
	}

	window->draw(sprite);
}

void CIMG::DrawVert(sf::RenderWindow* window, int iXOffset, int iYOffset) {
	sprite.setPosition(iXOffset, iYOffset);
	sprite.setRotation(180);
	sprite.setScale(-1, 1);
	window->draw(sprite);
}

void CIMG::Draw(sf::RenderWindow* window, sf::IntRect rCrop, sf::IntRect rRect) {
	sprite.setTextureRect(rCrop);
	sprite.setPosition(rRect.left, rRect.top);
	sprite.setScale(
		(float)rRect.width / rCrop.width,
		(float)rRect.height / rCrop.height
	);
	window->draw(sprite);
}

/* ******************************************** */

void CIMG::setIMG(std::string fileName, sf::RenderWindow* window) {
	fileName = "files/images/" + fileName + ".bmp";

	if (!tIMG.loadFromFile(fileName)) {
		// Handle error - texture failed to load
		return;
	}

	// Set magenta (255,0,255) as transparent color
	sf::Image img = tIMG.copyToImage();
	img.createMaskFromColor(sf::Color(255, 0, 255));
	tIMG.loadFromImage(img);

	sprite.setTexture(tIMG);

	sf::Vector2u size = tIMG.getSize();
	rRect.left = 0;
	rRect.top = 0;
	rRect.width = size.x;
	rRect.height = size.y;
}

sf::Texture* CIMG::getIMG() {
	return &tIMG;
}

sf::IntRect CIMG::getRect() {
	return rRect;
}
