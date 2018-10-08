//
// Whip.h
//

#ifndef __WHIP_H__
#define __WHIP_H__

#include "Object.h"
#include "Hero.h"
#include "EventCollision.h"

class Whip : public df::Object {

private:
	int removal_countdown;
	Hero *this_hero;

	void step();
	void hit(const df::EventCollision *p_collision_event);

public:
	Whip(Hero *h);
	~Whip();
	int eventHandler(const df::Event *p_e);
};

#endif // !__WHIP_H__
