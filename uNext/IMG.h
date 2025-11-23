#pragma once

#ifndef IMG_H
#define IMG_H

#include "header.h"

class CIMG
{
private:
	sf::Texture tIMG;
	sf::Sprite sprite;
	sf::Vector2f position;
	sf::IntRect rRect;

public:
	CIMG(void);
	CIMG(std::string fileName, sf::RenderWindow* window);
	~CIMG(void);

	void Draw(sf::RenderWindow* window, int iXOffset, int iYOffset);
	void Draw(sf::RenderWindow* window, int iXOffset, int iYOffset, bool bRotate);
	void DrawVert(sf::RenderWindow* window, int iXOffset, int iYOffset);
	void Draw(sf::RenderWindow* window, sf::IntRect rCrop, sf::IntRect rRect);

	/* ----- get & set ----- */
	sf::Texture* getIMG();
	void setIMG(std::string fileName, sf::RenderWindow* window);
	sf::IntRect getRect();
};

#endif