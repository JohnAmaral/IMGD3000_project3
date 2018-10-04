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
	int move_slowdown; // moving
	int move_countdown;
	int melee_slowdown; // melee attack
	int melee_countdown;
	int fire_slowdown; // ranged attack
	int fire_countdown;
	int lives_count; // number of lives
	int hit_slowdown; // getting hit
	int hit_countdown;
	int bandit_score_to_reach; // keeps track of every 500 points earned
	int num_bandits; // number of bandits to spawn with every 500 points
	int lives_score_to_reach; // keeps track of every 1000 points earned

	bool jumping; // is Hero jumping currently

	df::ViewObject *score; // ViewObject for keeping score
	df::ViewObject *lives; // ViewObject for lives count

	Reticle *p_reticle; // reticle for shooting

	void kbd(const df::EventKeyboard *p_keyboard_event);
	void move(float dx);
	void step();
	void jump();
	void punch(); // melee attack
	void fire(df::Vector target); // ranged attack
	void mouse(const df::EventMouse *p_mouse_event);
	void hit(const df::EventCollision *p_collision_event);

public:
	Hero();
	~Hero();
	int eventHandler(const df::Event *p_e);
};

#endif // !__HERO_H__