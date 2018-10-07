#pragma once
// GameStart.h

#ifndef __GAME_START_H__
#define __GAME_START_H__

// Include statements.
#include "ViewObject.h"
#include "Music.h"

class GameStart : public df::ViewObject {

private:
	void start(bool character_choice);
	df::Music *t_music; // used for playing Game Start music

public:
	GameStart(); // constructor
	int eventHandler(const df::Event *p_e);
	void draw();
	void playMusic();
};

#endif // !__GAME_START_H__