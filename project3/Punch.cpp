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

	df::Sprite *p_temp_sprite = RM.getSprite("punch");
	if (!p_temp_sprite) {
		LM.writeLog("Punch::Punch(): Warning! Sprite '%s' not found", "punch");
	}
	else {
		setSprite(p_temp_sprite);
		setSpriteSlowdown(5);
	}

	// Set object type
	setType("Punch");
	this_hero = h;

	df::Vector p(this_hero->getPosition().getX() + 2, this_hero->getPosition().getY());
	setPosition(p);

	// Make the punch soft so can pass through hero
	setSolidness(df::SOFT);
	removal_countdown = 10;
	registerInterest(df::STEP_EVENT);
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

		// Link to "sheriff gun" sprite
		df::Sprite *p_temp_sprite;
		p_temp_sprite = RM.getSprite("sheriff gun");
		if (!p_temp_sprite) {
			LM.writeLog("Hero::Hero(): Warning! Sprite '%s' not found", "sheriff");
		}
		else {
			this_hero->setSprite(p_temp_sprite);
			this_hero->setSpriteSlowdown(3); // 1/3 speed animation
			this_hero->setTransparency(); // Transparent sprite
		}

		WM.markForDelete(this);
	}

	df::Vector p(this_hero->getPosition().getX() + 2, this_hero->getPosition().getY());
	setPosition(p);
}

void Punch::hit(const df::EventCollision *p_collision_event) {
	if ((p_collision_event->getObject1()->getType() == "Vulture") ||
		(p_collision_event->getObject2()->getType() == "Vulture")) {
		WM.markForDelete(p_collision_event->getObject1());
		WM.markForDelete(p_collision_event->getObject2());

		// Increment score by 50 points
		df::EventView ev("Score", 100, true);
		WM.onEvent(&ev);

		/*if (ev.getValue() == 500) {
			for (int i = 0; i < 3; i++)
				new Bandit();
		}*/

	}
	/*if ((p_collision_event->getObject1()->getType() == "Bandit") ||
		(p_collision_event->getObject2()->getType() == "Bandit")) {

		//WM.markForDelete(p_collision_event->getObject1());
		//WM.markForDelete(p_collision_event->getObject2());

		// Increment score by 50 points
		df::EventView ev("Score", 200, true);
		WM.onEvent(&ev);
	}*/
}