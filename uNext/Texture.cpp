#include "Texture.h"
#include "header.h"

using namespace std;

/* ******************************************** */

Texture::Texture(string fileName) {
	//IMG_LoadTexture(renderer, fileName.c_str());

}

Texture::~Texture(void) {
	delete texture;
}

/* ******************************************** */

void Texture::Draw() { Texture::Draw(0, 0); }

void Texture::Draw(int offsetX, int offsetY) {

}

/* ******************************************** */

sf::Texture* Texture::getTexture() {
	return texture;
}