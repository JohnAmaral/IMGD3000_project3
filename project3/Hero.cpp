//
// Hero.cpp
//

#include "Hero.h"
#include "Bullet.h"
#include "Punch.h"
#include "Whip.h"
#include "LogManager.h"
#include "GameManager.h"
#include "WorldManager.h"
#include "ResourceManager.h"
#include "EventStep.h"
#include "EventView.h"
#include "GameOver.h"
#include "Bandit.h"
#include "Skull.h"

Hero::Hero(bool character_choice) {

	melee_slowdown = 15;
	melee_countdown = melee_slowdown;
	move_slowdown = 2;
	move_countdown = move_slowdown;
	fire_slowdown = 15;
	fire_countdown = fire_slowdown;
	lives_count = 5;
	hit_slowdown = 30;
	hit_countdown = hit_slowdown;
	lastMovedRight = true;
	using_weapon = false;
	alignment = character_choice;

	bandit_score_to_reach = 250;
	bandit_score_to_reach_odd = 1000;
	bandit_score_to_reach_even = 2000;

	num_bandits_to_generate = 0;
	bandit_rand_num = 3;
	bandit_inc_num = 0;

	lives_score_to_reach = 1500;

	// Set altitude to higher than other objects
	setAltitude(3);

	// Set score ViewObject
	score = new df::ViewObject;
	score->setLocation(df::TOP_RIGHT); // top right of window
	score->setViewString("Score");
	score->setValue(0); // initially 0 points
	score->setColor(df::GREEN); // green display

	// Create display for health count.
	lives = new df::ViewObject;
	lives->setLocation(df::TOP_LEFT); // top left of window
	lives->setViewString("Lives");
	lives->setValue(5); // initially 6 hit points
	lives->setColor(df::RED); // yellow display

	// if the player chose to play as the sheriff, load sheriff sprite
	if (alignment) {
		// Link to "sheriff right" sprite
		df::Sprite *p_temp_sprite;
		p_temp_sprite = RM.getSprite("sheriff right");
		if (!p_temp_sprite) {
			LM.writeLog("Hero::Hero(): Warning! Sprite '%s' not found", "sheriff right");
		}
		else {
			setSprite(p_temp_sprite);
			setSpriteSlowdown(3); // 1/3 speed animation
			setTransparency(); // Transparent sprite
		}
	}
	else {
		// Link to "outlaw right" sprite
		df::Sprite *p_temp_sprite;
		p_temp_sprite = RM.getSprite("outlaw right");
		if (!p_temp_sprite) {
			LM.writeLog("Hero::Hero(): Warning! Sprite '%s' not found", "outlaw right");
		}
		else {
			setSprite(p_temp_sprite);
			setSpriteSlowdown(3); // 1/3 speed animation
			setTransparency(); // Transparent sprite
		}
	}
	

	registerInterest(df::MOUSE_EVENT);
	registerInterest(df::KEYBOARD_EVENT);
	registerInterest(df::STEP_EVENT);
	registerInterest(df::COLLISION_EVENT);

	setType("Sheriff");
	df::Vector p(WM.getBoundary().getHorizontal() / 2, WM.getBoundary().getVertical() - 3);
	setPosition(p);

	// Create reticle for shooting
	p_reticle = new Reticle();
	p_reticle->draw();
}

Hero::~Hero() {
	GameOver *p_go = new GameOver();

	// Mark reticle for deletion
	WM.markForDelete(p_reticle);
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

	// If collides with Vultures or Bandits, check lives
	// If run out, mark both objects for destruction
	if ((p_collision_event->getObject1()->getType() == "Vulture") ||
		(p_collision_event->getObject2()->getType() == "Vulture") ||
		(p_collision_event->getObject1()->getType() == "Bandit") ||
		(p_collision_event->getObject2()->getType() == "Bandit")) {

		if (hit_countdown > 0) {
			return;
		}

		hit_countdown = hit_slowdown;
		df::EventView ev("Lives", -1, true);
		WM.onEvent(&ev);
		lives_count--;

		if (!lives_count) {

			if ((p_collision_event->getObject1()->getType()) == "Sheriff") {
				WM.markForDelete(p_collision_event->getObject1());
			}

			if ((p_collision_event->getObject2()->getType()) == "Sheriff") {
				WM.markForDelete(p_collision_event->getObject2());
			}

			// Play sheriff death sound
			df::Sound *p_sound = RM.getSound("sheriff death");
			p_sound->play();

			// Create Skull icon
			Skull *p_skull = new Skull();
			p_skull->setPosition(this->getPosition());

			return;
		}
		// Play sheriff hit sound
		df::Sound *p_sound = RM.getSound("sheriff hit");
		p_sound->play();
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

	// Hit countdown
	hit_countdown--;
	if (hit_countdown < 0) {
		hit_countdown = 0;
	}

	// If at peak height of jumping, move back down to ground
	if (getPosition().getY() == 12) {
		setVelocity(df::Vector(0, 0.5));
		jumping = false;
	}

	// If starting jump, move up
	if (getPosition().getY() == 21 && !jumping) {
		setVelocity(df::Vector(0, 0));
	}

	// Check score to increase range of Bandits to spawn
	if (score->getValue() >= bandit_score_to_reach_odd) {

		// Increase range of bandits to spawn
		bandit_rand_num--;
		bandit_inc_num++;
		bandit_score_to_reach_odd += 2000;
	}

	// Check score to increase range of Bandits to spawn
	if (score->getValue() >= bandit_score_to_reach_even) {

		// Increase range of bandits to spawn
		bandit_rand_num++;
		bandit_score_to_reach_even += 2000;
	}

	// Check score to start spawning Bandits
	if (score->getValue() >= bandit_score_to_reach) {
		num_bandits_to_generate = rand() % bandit_rand_num + bandit_inc_num;
		for (int i = 0; i < num_bandits_to_generate; i++) {
			new Bandit();
		}
		bandit_score_to_reach += 250;
		if (bandit_score_to_reach == 500) {
			if (alignment) {
				// Play sheriff taunt sound
				df::Sound *p_sound = RM.getSound("sheriff taunt");
				p_sound->play();
			}
			else {
				// Play outlaw taunt sound
				df::Sound *p_sound = RM.getSound("outlaw taunt");
				p_sound->play();
			}
		}
	}

	// Check score to add extra life
	if (score->getValue() >= lives_score_to_reach) {
		// Increment lives by 1
		df::EventView ev("Lives", 1, true);
		WM.onEvent(&ev);
		lives_count++;

		lives_score_to_reach += 1500;
	}
}

// Take appropriate action according to key pressed
void Hero::kbd(const df::EventKeyboard *p_keyboard_event) {

	switch (p_keyboard_event->getKey()) {
	case df::Keyboard::Q: { // quit
		if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED) {
			WM.markForDelete(this);
			df::EventView ev("Lives", -(lives_count), true);
			WM.onEvent(&ev);
			lives_count = 0;
		}
		break;
	}
	case df::Keyboard::A: { // left
		if (p_keyboard_event->getKeyboardAction() == df::KEY_DOWN) {
			move(-1.5);
		}
		break;
	}
	case df::Keyboard::D: { // right
		if (p_keyboard_event->getKeyboardAction() == df::KEY_DOWN) {
			move(+1.5);
		}
		break;
	}
	case df::Keyboard::LEFTARROW: { // left
		if (p_keyboard_event->getKeyboardAction() == df::KEY_DOWN) {
			move(-1.5);
		}
		break;
	}
	case df::Keyboard::RIGHTARROW: { // right
		if (p_keyboard_event->getKeyboardAction() == df::KEY_DOWN) {
			move(+1.5);
		}
		break;
	}
	case df::Keyboard::SPACE: {
		if ((p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED) && (getPosition().getY() == 21)) {
			jump();
		}
		break;
	}
	}
}

// Jump up and land on ground
void Hero::jump() {
	setVelocity(df::Vector(0, -0.5));
	jumping = true;
	return;
}

// Move left and right
void Hero::move(float dx) {

	// See if time to move
	if (move_countdown > 0) {
		return;
	}
	move_countdown = move_slowdown;

	if (using_weapon) {
		// Don't change sprite
		if (dx >= 0) {
			lastMovedRight = true;
		}
		else {
			lastMovedRight = false;
		}
	}
	else if (dx >= 0 && alignment) {
		// Link to "sheriff right" sprite
		df::Sprite *p_temp_sprite;
		p_temp_sprite = RM.getSprite("sheriff right");
		if (!p_temp_sprite) {
			LM.writeLog("Hero::Hero(): Warning! Sprite '%s' not found", "sheriff right");
		}
		else {
			setSprite(p_temp_sprite);
			setSpriteSlowdown(3); // 1/3 speed animation
			setTransparency(); // Transparent sprite
		}

		lastMovedRight = true;
	}
	else if (dx >= 0 && !alignment) {
		// Link to "outlaw right" sprite
		df::Sprite *p_temp_sprite;
		p_temp_sprite = RM.getSprite("outlaw right");
		if (!p_temp_sprite) {
			LM.writeLog("Hero::Hero(): Warning! Sprite '%s' not found", "outlaw right");
		}
		else {
			setSprite(p_temp_sprite);
			setSpriteSlowdown(3); // 1/3 speed animation
			setTransparency(); // Transparent sprite
		}

		lastMovedRight = true;
	}
	else if (dx <= 0 && alignment) {
		// Link to "sheriff left" sprite
		df::Sprite *p_temp_sprite;
		p_temp_sprite = RM.getSprite("sheriff left");
		if (!p_temp_sprite) {
			LM.writeLog("Hero::Hero(): Warning! Sprite '%s' not found", "sheriff left");
		}
		else {
			setSprite(p_temp_sprite);
			setSpriteSlowdown(3); // 1/3 speed animation
			setTransparency(); // Transparent sprite
		}

		lastMovedRight = false;
	}
	else {
		// Link to "outlaw left" sprite
		df::Sprite *p_temp_sprite;
		p_temp_sprite = RM.getSprite("outlaw left");
		if (!p_temp_sprite) {
			LM.writeLog("Hero::Hero(): Warning! Sprite '%s' not found", "outlaw left");
		}
		else {
			setSprite(p_temp_sprite);
			setSpriteSlowdown(3); // 1/3 speed animation
			setTransparency(); // Transparent sprite
		}

		lastMovedRight = false;
	}

	// If stays on window, allow move
	df::Vector new_pos(getPosition().getX() + dx, getPosition().getY());
	if ((new_pos.getY() > 3) && (new_pos.getY() < WM.getBoundary().getVertical() - 2) &&
		(new_pos.getX() > 0) && (new_pos.getX() < WM.getBoundary().getHorizontal())) {
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

	// Makes the outlaws gun a little slower
	if (alignment) {
		v.scale(1);
	}
	else {
		v.scale(0.75);
	}
	
	Bullet *p = new Bullet(getPosition());
	p->setVelocity(v);

	// Play "fire" sound
	df::Sound *p_sound = RM.getSound("fire");
	p_sound->play();
}

void Hero::punch() {
	if (melee_countdown > 0) {
		return;
	}
	melee_countdown = melee_slowdown;

	// Link to "sheriff nothing" sprite
	df::Sprite *p_temp_sprite;
	p_temp_sprite = RM.getSprite("sheriff nothing");
	if (!p_temp_sprite) {
		LM.writeLog("Hero::punch(): Warning! Sprite '%s' not found", "sheriff nothing");
	}
	else {
		setSprite(p_temp_sprite);
		setSpriteSlowdown(3); // 1/3 speed animation
		setTransparency(); // Transparent sprite
	}

	Punch *p = new Punch(this);
	using_weapon = true;

	// Play punch sound
	df::Sound *p_sound = RM.getSound("punch");
	p_sound->play();
}

void Hero::whip(bool sideways) {
	if (melee_countdown > 0) {
		return;
	}
	melee_countdown = melee_slowdown;

	// Link to "sheriff nothing" sprite
	df::Sprite *p_temp_sprite;
	p_temp_sprite = RM.getSprite("sheriff nothing");
	if (!p_temp_sprite) {
		LM.writeLog("Hero::whip(): Warning! Sprite '%s' not found", "sheriff nothing");
	}
	else {
		setSprite(p_temp_sprite);
		setSpriteSlowdown(3); // 1/3 speed animation
		setTransparency(); // Transparent sprite
	}

	if (sideways) {
		Whip *p = new Whip(this, true);
	}
	else {
		Whip *p = new Whip(this, false);
	}
	
	using_weapon = true;

	// Play "whip" sound.
	df::Sound *v_sound = RM.getSound("whip");
	v_sound->play();
}

void Hero::mouse(const df::EventMouse *p_mouse_event) {

	// Pressed left button?
	if ((p_mouse_event->getMouseAction() == df::CLICKED) &&
		(p_mouse_event->getMouseButton() == df::Mouse::LEFT)) {
		if (alignment) {
			punch();
		}
		else {
			whip(true);
		}
	}

	// Pressed right button?
	if ((p_mouse_event->getMouseAction() == df::CLICKED) &&
		(p_mouse_event->getMouseButton() == df::Mouse::RIGHT)) {
		if (alignment) {
			fire(p_mouse_event->getMousePosition());
		}
		else {
			whip(false);
		}
	}
}

bool Hero::getLastMovement() const {
	return lastMovedRight;
}

bool Hero::isSheriff() const {
	return alignment;
}
