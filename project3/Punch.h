//
// Punch.h
//

#ifndef __PUNCH_H__
#define __PUNCH_H__

#include "Object.h"
#include "Hero.h"
#include "EventCollision.h"

class Punch : public df::Object {

private:
	int removal_countdown;
	Hero *this_hero;

	void step();
	void hit(const df::EventCollision *p_collision_event);

public:
	Punch(Hero *h);
	int eventHandler(const df::Event *p_e);
};

#endif // !__PUNCH_H__