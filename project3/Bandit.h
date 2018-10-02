#pragma once
// Bandit.h

#ifndef __BANDIT_H__
#define __BANDIT_H__

// Include statements.
#include "Enemy.h"
#include "EventCollision.h"

class Bandit : public Enemy {

public:
	Bandit(); // constructor
	int eventHandler(const df::Event *p_e);

private:
	void out();
	void moveToStart();
	void hit(const df::EventCollision *p_collision_event);
};

#endif // !__BANDIT_H__
