#pragma once
// Bandit.h

#ifndef __BANDIT_H__
#define __BANDIT_H__

// Include statements.
#include "Enemy.h"
#include "EventCollision.h"
#include "Whip.h"
#include "Punch.h"

class Bandit : public Enemy {

public:
	Bandit(); // constructor
	int eventHandler(const df::Event *p_e);

private:
	int health_count; // keep track of bandit health (can be hit twice)

	void out();
	void moveToStart();
	void hit(const df::EventCollision *p_collision_event);
};

#endif // !__BANDIT_H__

