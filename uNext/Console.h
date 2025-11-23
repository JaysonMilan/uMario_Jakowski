#pragma once

#ifndef CONSOLE_H
#define CONOSLE_H

#include "header.h"
#include <vector>

class Console
{
private:
	sf::IntRect rRect;

	std::vector<std::string> vPrint;

	unsigned int iMax;
public:
	Console(void);
	~Console(void);

	void Draw(sf::RenderWindow* rR);

	void print(int);
	void print(std::string sPrint);
};

#endif