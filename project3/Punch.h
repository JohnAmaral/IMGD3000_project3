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
	int hit_slowdown;
	int hit_countdown;
	Hero *this_hero;

	void step();
	void hit(const df::EventCollision *p_collision_event);

public:
	Punch(Hero *h);
	~Punch();
	bool allowedToSetSprite;
	int eventHandler(const df::Event *p_e);
	bool isInvincible() const;
};

#endif // !__PUNCH_H__