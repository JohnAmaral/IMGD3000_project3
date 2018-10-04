#pragma once
// GameStart.h

#ifndef __GAME_START_H__
#define __GAME_START_H__

// Include statements.
#include "ViewObject.h"
#include "Music.h"

class GameStart : public df::ViewObject {

private:
	void start();
	df::Music *t_music; // used for playing Game Start music
	df::Music *g_music; // used for background music during gameplay

public:
	GameStart(); // constructor
	int eventHandler(const df::Event *p_e);
	void draw();
	void playMusic();
};

#endif // !__GAME_START_H__