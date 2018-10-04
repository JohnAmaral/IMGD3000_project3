#pragma once
// GameOver.h

#ifndef __GAME_OVER_H__
#define __GAME_OVER_H__

// Include statements.
#include "ViewObject.h"
#include "Music.h"

class GameOver : public df::ViewObject {

private:
	int time_to_live; // game over message is temporary
	void step();

public:
	GameOver(); // constructor
	~GameOver(); // destructor
	int eventHandler(const df::Event *p_e);
	void draw();
};

#endif // !__GAME_OVER_H__