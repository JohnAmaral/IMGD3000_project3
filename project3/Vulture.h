#pragma once
// Vulture.h

// Include statements.
#include "Enemy.h"
#include "EventCollision.h"

class Vulture : public Enemy {

public:
	Vulture(); // constructor
	int eventHandler(const df::Event *p_e);

private:
	void out();
	void moveToStart();
	void hit(const df::EventCollision *p_collision_event);
};