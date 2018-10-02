#pragma once
// Vulture.h

#ifndef __VULTURE_H__
#define __VULTURE_H__

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

#endif // !__VULTURE_H__