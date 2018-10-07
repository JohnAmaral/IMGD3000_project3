#pragma once
// Skull.h

// Include statements.
#include "Object.h"

class Skull : public df::Object {

private:
	int screen_time; // skull is temporary
	void step();

public:
	Skull();
	int eventHandler(const df::Event *p_e);
};