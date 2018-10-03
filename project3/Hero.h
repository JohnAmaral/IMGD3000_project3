//
// Hero.h
//

#ifndef __HERO_H__
#define __HERO_H__

#include "Object.h"
#include "Reticle.h"
#include "EventKeyboard.h"
#include "EventMouse.h"
#include "EventCollision.h"
#include "ViewObject.h"

class Hero : public df::Object {

private:
	int move_slowdown;
	int move_countdown;
	int melee_slowdown;
	int melee_countdown;
	int fire_slowdown;
	int fire_countdown;
	int lives_count;
	int hit_slowdown;
	int hit_countdown;
	bool jumping;
	df::ViewObject *score;
	df::ViewObject *lives;

	Reticle *p_reticle;

	void kbd(const df::EventKeyboard *p_keyboard_event);
	void move(float dx);
	void step();
	void jump();
	void punch();
	void fire(df::Vector target);
	void mouse(const df::EventMouse *p_mouse_event);
	void hit(const df::EventCollision *p_collision_event);

public:
	Hero();
	~Hero();
	int eventHandler(const df::Event *p_e);
};

#endif // !__HERO_H__