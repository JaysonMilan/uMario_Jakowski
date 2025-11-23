#pragma once

#include <string>
#include <SFML/Graphics.hpp>

class Texture
{
public:
	Texture(std::string fileName);
	~Texture(void);

	void Draw();
	void Draw(int offsetX, int offsetY);

	sf::Texture* getTexture();
private:
	sf::Texture* texture;


};

