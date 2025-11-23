#pragma once

#ifndef PAUSEMENU_H
#define PAUSEMENU_H

#include "Menu.h"

class PauseMenu : public Menu
{
private:
	sf::IntRect rPause;
public:
	PauseMenu(void);
	~PauseMenu(void);

	void Update();
	void Draw(sf::RenderWindow* rR);

	void enter();
	void escape();

	void updateActiveButton(int iDir);
};

#endif