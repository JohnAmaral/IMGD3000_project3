#pragma once
// GameOver.h

// Include statements.
#include "ViewObject.h"
#include "Music.h"

class GameOver : public df::ViewObject {

private:
	int time_to_live; // game over message is temporary
	void step();
	df::Music *g_music; // used for stopping background game music

public:
	GameOver(); // constructor
	~GameOver(); // destructor
	int eventHandler(const df::Event *p_e);
	void draw();
};