//
// Hero.cpp
//

#include "Hero.h"
#include "Bullet.h"
#include "LogManager.h"
#include "GameManager.h"
#include "WorldManager.h"
#include "ResourceManager.h"
#include "EventStep.h"
#include "EventView.h"
#include "GameOver.h"

Hero::Hero() {

	move_slowdown = 2;
	move_countdown = move_slowdown;
	fire_slowdown = 15;
	fire_countdown = fire_slowdown;
	lives_count = 2;

	// Link to "sheriff" sprite
	df::Sprite *p_temp_sprite;
	p_temp_sprite = RM.getSprite("sheriff");
	if (!p_temp_sprite) {
		LM.writeLog("Hero::Hero(): Warning! Sprite '%s' not found", "sheriff");
	}
	else {
		setSprite(p_temp_sprite);
		setSpriteSlowdown(3); // 1/3 speed animation
		setTransparency(); // Transparent sprite
	}

	registerInterest(df::MOUSE_EVENT);
	registerInterest(df::KEYBOARD_EVENT);
	registerInterest(df::STEP_EVENT);
	registerInterest(df::COLLISION_EVENT);

	setType("Sheriff");
	df::Vector p(WM.getBoundary().getHorizontal() / 2, WM.getBoundary().getVertical() / 2);
	setPosition(p);
}

Hero::~Hero() {
	GameOver *p_go = new GameOver();
}

int Hero::eventHandler(const df::Event *p_e) {
	if (p_e->getType() == df::KEYBOARD_EVENT) {
		const df::EventKeyboard *p_keyboard_event =
			dynamic_cast <const df::EventKeyboard *> (p_e);
		kbd(p_keyboard_event);
		return 1;
	}

	if (p_e->getType() == df::STEP_EVENT) {
		step();
		return 1;
	}

	if (p_e->getType() == df::MOUSE_EVENT) {
		const df::EventMouse *p_mouse_event =
			dynamic_cast <const df::EventMouse *> (p_e);
		mouse(p_mouse_event);
		return 1;
	}

	if (p_e->getType() == df::COLLISION_EVENT) {
		const df::EventCollision *p_collision_event =
			dynamic_cast <const df::EventCollision *> (p_e);
		hit(p_collision_event);
		return 1;
	}

	return 0;
}

void Hero::hit(const df::EventCollision *p_collision_event) {

	// If collides with saucers, check lives
	// If run out, mark both objects for destruction
	if (((p_collision_event->getObject1()->getType()) == "Drunk") ||
		((p_collision_event->getObject2()->getType()) == "Drunk")) {

		if (!lives_count) {
			
			if ((p_collision_event->getObject1()->getType()) == "Sheriff") {
				WM.markForDelete(p_collision_event->getObject1());
			}

			if ((p_collision_event->getObject2()->getType()) == "Sheriff") {
				WM.markForDelete(p_collision_event->getObject2());
			}
			return;
		}
		lives_count--;
		
		// Send "view" event with lives to interested ViewObjects
		//df::EventView ev("Lives", -1, true);
		//WM.onEvent(&ev);
	}
}

// Decrease rate restriction counters
void Hero::step() {
	// Move countdown
	move_countdown--;
	if (move_countdown < 0) {
		move_countdown = 0;
	}

	// Melee countdown
	melee_countdown--;
	if (melee_countdown < 0) {
		melee_countdown = 0;
	}

	// Fire countdown
	fire_countdown--;
	if (fire_countdown < 0) {
		fire_countdown = 0;
	}
}

// Take appropriate action according to key pressed
void Hero::kbd(const df::EventKeyboard *p_keyboard_event) {

	switch (p_keyboard_event->getKey()) {
	case df::Keyboard::Q: { // quit
		if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED) {
			WM.markForDelete(this);
		}
		break;
	}
	case df::Keyboard::W: { // up
		if (p_keyboard_event->getKeyboardAction() == df::KEY_DOWN) {
			move(0,-0.5);
		}
		break;
	}
	case df::Keyboard::S: { // down
		if (p_keyboard_event->getKeyboardAction() == df::KEY_DOWN) {
			move(0,+0.5);
		}
		break;
	}
	case df::Keyboard::A: { // left
		if (p_keyboard_event->getKeyboardAction() == df::KEY_DOWN) {
			move(-1.5, 0);
		}
		break;
	}
	case df::Keyboard::D: { // right
		if (p_keyboard_event->getKeyboardAction() == df::KEY_DOWN) {
			move(+1.5,0);
		}
		break;
	}
	case df::Keyboard::SPACE: {
		if (p_keyboard_event->getKeyboardAction() == df::KEY_DOWN) {
			jump();
		}
		break;
	}
	}
}

// Jump up and land on ground
void Hero::jump() {
	return;
}

// Move up and down
void Hero::move(float dx, float dy) {

	// See if time to move
	if (move_countdown > 0) {
		return;
	}
	move_countdown = move_slowdown;

	// If stays on window, allow move
	df::Vector new_pos(getPosition().getX() + dx, getPosition().getY() + dy);
	if ((new_pos.getY() > 3) && (new_pos.getY() < WM.getBoundary().getVertical()) &&
		(new_pos.getX() > 3) && (new_pos.getX() < WM.getBoundary().getHorizontal())) {
		WM.moveObject(this, new_pos);
	}
}

void Hero::fire(df::Vector target) {
	if (fire_countdown > 0) {
		return;
	}
	fire_countdown = fire_slowdown;

	// Fire bullet towards target
	// Compute normalized vector to position, then scale by speed (1)
	df::Vector v = target - getPosition();
	v.normalize();
	v.scale(1);
	Bullet *p = new Bullet(getPosition());
	p->setVelocity(v);

	// Play "fire" sound
	df::Sound *p_sound = RM.getSound("fire");
	p_sound->play();
}

void Hero::mouse(const df::EventMouse *p_mouse_event) {

	// Pressed left button?
	if ((p_mouse_event->getMouseAction() == df::CLICKED) &&
		(p_mouse_event->getMouseButton() == df::Mouse::LEFT)) {
		fire(p_mouse_event->getMousePosition());
	}

	// Pressed right button?
	if ((p_mouse_event->getMouseAction() == df::CLICKED) &&
		(p_mouse_event->getMouseButton() == df::Mouse::RIGHT)) {
		fire(p_mouse_event->getMousePosition());
	}
}
