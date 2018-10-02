#pragma once
// Enemy.h

// Include statements.
#include "Object.h"
#include "EventCollision.h"

class Enemy : public df::Object {

public:
	Enemy(); // constructor
	int eventHandler(const df::Event *p_e);

protected:
	void out();
	virtual void moveToStart();
	virtual void hit(const df::EventCollision *p_collision_event);
};
