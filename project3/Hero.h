//
// Hero.h
//

#include "Object.h"
#include "EventKeyboard.h"
#include "EventMouse.h"
#include "EventCollision.h"

class Hero : public df::Object {

private:
	int move_slowdown;
	int move_countdown;
	int melee_slowdown;
	int melee_countdown;
	int fire_slowdown;
	int fire_countdown;
	int lives_count;
	bool jumping;
	bool isMoving;

	void kbd(const df::EventKeyboard *p_keyboard_event);
	void move(float dx);
	void step();
	void jump();
	void fire(df::Vector target);
	void mouse(const df::EventMouse *p_mouse_event);
	void hit(const df::EventCollision *p_collision_event);

public:
	Hero();
	~Hero();
	int eventHandler(const df::Event *p_e);
};