//
// Punch.cpp
// 

#include "Punch.h"
#include "LogManager.h"
#include "WorldManager.h"
#include "ResourceManager.h"
#include "EventView.h"
#include "EventStep.h"

Punch::Punch(Hero *h) {

	// Set object type
	setType("Punch");
	this_hero = h;

	if (this_hero->getLastMovement()) {
		df::Sprite *p_temp_sprite = RM.getSprite("punch right");
		if (!p_temp_sprite) {
			LM.writeLog("Punch::Punch(): Warning! Sprite '%s' not found", "punch right");
		}
		else {
			setSprite(p_temp_sprite);
			setSpriteSlowdown(5);
			setTransparency('#');
		}
	}
	else {
		df::Sprite *p_temp_sprite = RM.getSprite("punch left");
		if (!p_temp_sprite) {
			LM.writeLog("Punch::Punch(): Warning! Sprite '%s' not found", "punch left");
		}
		else {
			setSprite(p_temp_sprite);
			setSpriteSlowdown(5);
			setTransparency('#');
		}
	}

	float x_pos = this_hero->getPosition().getX();
	float y_pos = this_hero->getPosition().getY();
	df::Vector p(x_pos + 5, y_pos);
	setPosition(p);

	// Make the punch soft so can pass through hero
	setSolidness(df::SOFT);
	removal_countdown = 15;
	registerInterest(df::STEP_EVENT);
}

Punch::~Punch() {
	if (this_hero->getLastMovement()) {
		// Link to "sheriff right" sprite
		df::Sprite *p_temp_sprite;
		p_temp_sprite = RM.getSprite("sheriff right");
		if (!p_temp_sprite) {
			LM.writeLog("Punch::step(): Warning! Sprite '%s' not found", "sheriff right");
		}
		else {
			this_hero->setSprite(p_temp_sprite);
			this_hero->setSpriteSlowdown(3); // 1/3 speed animation
			this_hero->setTransparency(); // Transparent sprite
		}
	}
	else {
		// Link to "sheriff left" sprite
		df::Sprite *p_temp_sprite;
		p_temp_sprite = RM.getSprite("sheriff left");
		if (!p_temp_sprite) {
			LM.writeLog("Punch::step(): Warning! Sprite '%s' not found", "sheriff left");
		}
		else {
			this_hero->setSprite(p_temp_sprite);
			this_hero->setSpriteSlowdown(3); // 1/3 speed animation
			this_hero->setTransparency(); // Transparent sprite
		}
	}

	this_hero->punching = false;
}

int Punch::eventHandler(const df::Event *p_e) {
	if (p_e->getType() == df::STEP_EVENT) {
		step();
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

void Punch::step() {

	removal_countdown--;
	if (removal_countdown < 0) {
		WM.markForDelete(this);
		return;
	}

	if (this_hero->getLastMovement()) {
		df::Sprite *p_temp_sprite = RM.getSprite("punch right");
		if (!p_temp_sprite) {
			LM.writeLog("Punch::Punch(): Warning! Sprite '%s' not found", "punch right");
		}
		else {
			setSprite(p_temp_sprite);
			setSpriteSlowdown(5);
			setTransparency('#');
		}
		df::Vector p(this_hero->getPosition().getX() + 5, this_hero->getPosition().getY());
		setPosition(p);
	}
	else {
		df::Sprite *p_temp_sprite = RM.getSprite("punch left");
		if (!p_temp_sprite) {
			LM.writeLog("Punch::Punch(): Warning! Sprite '%s' not found", "punch left");
		}
		else {
			setSprite(p_temp_sprite);
			setSpriteSlowdown(5);
			setTransparency('#');
		}
		df::Vector p(this_hero->getPosition().getX() - 5, this_hero->getPosition().getY());
		setPosition(p);
	}
	
}

void Punch::hit(const df::EventCollision *p_collision_event) {
	if ((p_collision_event->getObject1()->getType() == "Vulture") ||
		(p_collision_event->getObject2()->getType() == "Vulture")) {
		WM.markForDelete(p_collision_event->getObject1());
		WM.markForDelete(p_collision_event->getObject2());

		// Play "vulture death" sound.
		df::Sound *v_sound = RM.getSound("vulture death");
		v_sound->play();

		// Increment score by 100 points
		df::EventView ev("Score", 100, true);
		WM.onEvent(&ev);
	}
}