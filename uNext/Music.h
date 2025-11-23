#pragma once

#ifndef MUSIC_H
#define MUSIC_H

#include <SFML/Audio.hpp>
#include <string>
#include <vector>

class Music
{
private:
	std::vector<sf::Music*> vMusic;
	std::vector<sf::SoundBuffer*> vChunkBuffers;
	std::vector<sf::Sound*> vChunk;

	int iVolume;
public:
	Music(void);
	~Music(void);

	bool musicStopped;

	enum eMusic {
		mNOTHING,
		mOVERWORLD,
		mOVERWORLDFAST,
		mUNDERWORLD,
		mUNDERWORLDFAST,
		mUNDERWATER,
		mUNDERWATERFAST,
		mCASTLE,
		mCASTLEFAST,
		mLOWTIME,
		mSTAR,
		mSTARFAST,
		mSCORERING,
	};

	eMusic currentMusic;

	enum eChunk {
		cCOIN,
		cBLOCKBREAK,
		cBLOCKHIT,
		cBOOM,
		cBOWSERFALL,
		cBRIDGEBREAK,
		cBULLETBILL,
		cDEATH,
		cFIRE,
		cFIREBALL,
		cGAMEOVER,
		cINTERMISSION,
		cJUMP,
		cJUMPBIG,
		cLEVELEND,
		cLOWTIME,
		cMUSHROOMAPPER,
		cMUSHROOMMEAT,
		cONEUP,
		cPASUE,
		cPIPE,
		cRAINBOOM,
		cSHOT,
		cSHRINK,
		cSTOMP,
		cSWIM,
		cVINE,
		cCASTLEEND,
		cPRINCESSMUSIC,
	};

	void changeMusic(bool musicByLevel, bool forceChange);

	void PlayMusic();
	void PlayMusic(eMusic musicID);
	void StopMusic();
	void PauseMusic();

	void PlayChunk(eChunk chunkID);

	sf::Music* loadMusic(std::string fileName);
	sf::Sound* loadChunk(std::string fileName);

	// -- get & set

	int getVolume();
	void setVolume(int iVolume);
};

#endif