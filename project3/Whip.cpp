//
// Punch.cpp
// 

#include "Whip.h"
#include "LogManager.h"
#include "WorldManager.h"
#include "ResourceManager.h"
#include "EventView.h"
#include "EventStep.h"

Whip::Whip(Hero *h, bool sideways) {

	// Set object type
	setType("Whip");
	this_hero = h;
	whippingbandits = sideways;

	if (this_hero->getLastMovement() && whippingbandits) {
		df::Sprite *p_temp_sprite = RM.getSprite("whip right");
		if (!p_temp_sprite) {
			LM.writeLog("Whip::Whip(): Warning! Sprite '%s' not found", "whip right");
		}
		else {
			setSprite(p_temp_sprite);
			setSpriteSlowdown(5);
			setTransparency('#');
		}
		float x_pos = this_hero->getPosition().getX();
		float y_pos = this_hero->getPosition().getY();
		df::Vector p(x_pos + 8, y_pos - 1);
		setPosition(p);
	}
	else if (!this_hero->getLastMovement() && whippingbandits) {
		df::Sprite *p_temp_sprite = RM.getSprite("whip left");
		if (!p_temp_sprite) {
			LM.writeLog("Whip::Whip(): Warning! Sprite '%s' not found", "whip left");
		}
		else {
			setSprite(p_temp_sprite);
			setSpriteSlowdown(5);
			setTransparency('#');
		}
		float x_pos = this_hero->getPosition().getX();
		float y_pos = this_hero->getPosition().getY();
		df::Vector p(x_pos - 8, y_pos - 1);
		setPosition(p);
	}
	else if (this_hero->getLastMovement() && !whippingbandits) {
		df::Sprite *p_temp_sprite = RM.getSprite("whip up right");
		if (!p_temp_sprite) {
			LM.writeLog("Whip::Whip(): Warning! Sprite '%s' not found", "whip up right");
		}
		else {
			setSprite(p_temp_sprite);
			setSpriteSlowdown(5);
			setTransparency('#');
		}
		float x_pos = this_hero->getPosition().getX();
		float y_pos = this_hero->getPosition().getY();
		df::Vector p(x_pos + 2, y_pos - 4);
		setPosition(p);
	}
	else {
		df::Sprite *p_temp_sprite = RM.getSprite("whip up left");
		if (!p_temp_sprite) {
			LM.writeLog("Whip::Whip(): Warning! Sprite '%s' not found", "whip up left");
		}
		else {
			setSprite(p_temp_sprite);
			setSpriteSlowdown(5);
			setTransparency('#');
		}
		float x_pos = this_hero->getPosition().getX();
		float y_pos = this_hero->getPosition().getY();
		df::Vector p(x_pos - 2, y_pos - 4);
		setPosition(p);
	}

	// Set as same altitude as hero
	setAltitude(3);

	// Make the punch soft so can pass through hero
	setSolidness(df::SOFT);

	removal_countdown = 15;
	registerInterest(df::STEP_EVENT);
}

Whip::~Whip() {
	if (this_hero->getLastMovement()) {
		// Link to "outlaw right" sprite
		df::Sprite *p_temp_sprite;
		p_temp_sprite = RM.getSprite("outlaw right");
		if (!p_temp_sprite) {
			LM.writeLog("Whip::~Whip(): Warning! Sprite '%s' not found", "outlaw right");
		}
		else {
			this_hero->setSprite(p_temp_sprite);
			this_hero->setSpriteSlowdown(3); // 1/3 speed animation
			this_hero->setTransparency(); // Transparent sprite
		}
	}
	else {
		// Link to "outlaw left" sprite
		df::Sprite *p_temp_sprite;
		p_temp_sprite = RM.getSprite("outlaw left");
		if (!p_temp_sprite) {
			LM.writeLog("Whip::~Whip(): Warning! Sprite '%s' not found", "outlaw left");
		}
		else {
			this_hero->setSprite(p_temp_sprite);
			this_hero->setSpriteSlowdown(3); // 1/3 speed animation
			this_hero->setTransparency(); // Transparent sprite
		}
	}

	this_hero->using_weapon = false;
}

int Whip::eventHandler(const df::Event *p_e) {
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

void Whip::step() {

	removal_countdown--;
	if (removal_countdown < 0) {
		WM.markForDelete(this);
		return;
	}

	if (this_hero->getLastMovement() && whippingbandits) {
		df::Sprite *p_temp_sprite = RM.getSprite("whip right");
		if (!p_temp_sprite) {
			LM.writeLog("Whip::step(): Warning! Sprite '%s' not found", "whip right");
		}
		else {
			setSprite(p_temp_sprite);
			setSpriteSlowdown(5);
			setTransparency('#');
		}
		float x_pos = this_hero->getPosition().getX();
		float y_pos = this_hero->getPosition().getY();
		df::Vector p(x_pos + 8, y_pos - 1);
		setPosition(p);
	}
	else if (!this_hero->getLastMovement() && whippingbandits) {
		df::Sprite *p_temp_sprite = RM.getSprite("whip left");
		if (!p_temp_sprite) {
			LM.writeLog("Whip::step(): Warning! Sprite '%s' not found", "whip left");
		}
		else {
			setSprite(p_temp_sprite);
			setSpriteSlowdown(5);
			setTransparency('#');
		}
		float x_pos = this_hero->getPosition().getX();
		float y_pos = this_hero->getPosition().getY();
		df::Vector p(x_pos - 8, y_pos - 1);
		setPosition(p);
	}
	else if (this_hero->getLastMovement() && !whippingbandits) {
		df::Sprite *p_temp_sprite = RM.getSprite("whip up right");
		if (!p_temp_sprite) {
			LM.writeLog("Whip::Whip(): Warning! Sprite '%s' not found", "whip up right");
		}
		else {
			setSprite(p_temp_sprite);
			setSpriteSlowdown(5);
			setTransparency('#');
		}
		float x_pos = this_hero->getPosition().getX();
		float y_pos = this_hero->getPosition().getY();
		df::Vector p(x_pos + 2, y_pos - 4);
		setPosition(p);
	}
	else {
		df::Sprite *p_temp_sprite = RM.getSprite("whip up left");
		if (!p_temp_sprite) {
			LM.writeLog("Whip::Whip(): Warning! Sprite '%s' not found", "whip up left");
		}
		else {
			setSprite(p_temp_sprite);
			setSpriteSlowdown(5);
			setTransparency('#');
		}
		float x_pos = this_hero->getPosition().getX();
		float y_pos = this_hero->getPosition().getY();
		df::Vector p(x_pos - 2, y_pos - 4);
		setPosition(p);
	}

}

void Whip::hit(const df::EventCollision *p_collision_event) {
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