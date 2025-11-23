#include "Console.h"
#include "CFG.h"

/* ******************************************** */

Console::Console(void) {
	rRect.left = 5;
	rRect.top = 5;
	rRect.width = 175;
	rRect.height = 105;

	this->iMax = (rRect.height - rRect.top)/12;
}

Console::~Console(void) {

}

/* ******************************************** */

void Console::Draw(sf::RenderWindow* rR) {
	if(vPrint.size() > 0) {
	
		for(int i = vPrint.size() - 1, j = 0; i >= 0; i--, j++) {
			CCFG::getText()->Draw(rR, vPrint[i], rRect.left + rRect.width - 5 - CCFG::getText()->getTextWidth(vPrint[i], 8), rRect.top + rRect.height - 5 - 8*(j+1) - 4*j, 8);
		}

	}
}

/* ******************************************** */

void Console::print(int iPrint) {
	print(std::to_string(iPrint));
}

void Console::print(std::string sPrint) {
	std::string nPrint;
	for(unsigned int i = 0; i < sPrint.size(); i++) {
		if(sPrint[i] >= 97 && sPrint[i] < 123) {
			nPrint += sPrint[i] - 32;
		} else {
			nPrint += sPrint[i];
		}
	}

	if(vPrint.size() >= iMax) {
		vPrint.erase(vPrint.begin());
	}

	vPrint.push_back(nPrint);
}