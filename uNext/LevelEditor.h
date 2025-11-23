#pragma once

#ifndef LEVELEDITOR_H
#define LEVELEDITOR_H

#include "header.h"

class LevelEditor
{
private:
	sf::IntRect rBlock;

	sf::IntRect rDrag;

	int currentBlockID;
public:
	LevelEditor(void);
	~LevelEditor(void);

	void Update();
	void Draw(sf::RenderWindow* rR);

	void mouseWheel(int Y);
	
	void editMap();

	void drawStruct(sf::RenderWindow* rR);
};

#endif