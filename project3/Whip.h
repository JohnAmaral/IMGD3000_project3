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
	bool whippingbandits;
	int hit_slowdown;
	int hit_countdown;
	Hero *this_hero;

	void step();
	void hit(const df::EventCollision *p_collision_event);

public:
	Whip(Hero *h, bool sideways);
	~Whip();
	bool allowedToSetSprite;
	int eventHandler(const df::Event *p_e);
	bool isInvincible() const;
};

#endif // !__WHIP_H__
