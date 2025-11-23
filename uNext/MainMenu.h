#pragma once

#ifndef MAINMENU_H
#define MAINMENU_H

#include "Menu.h"

class MainMenu : public Menu
{
private:
	bool selectWorld;
	int activeWorldID, activeSecondWorldID;

	sf::IntRect rSelectWorld;
public:
	MainMenu(void);
	~MainMenu(void);

	void Update();
	void Draw(sf::RenderWindow* rR);

	void enter();
	void escape();

	void updateActiveButton(int iDir);
};

#endif