// 
// Bullet.cpp
// 

#include "Bullet.h"
#include "LogManager.h"
#include "WorldManager.h"
#include "ResourceManager.h"
#include "EventOut.h"
#include "EventView.h"
#include "Bandit.h"

Bullet::Bullet(df::Vector hero_pos) {

	// Setup "bullet" sprite
	df::Sprite *p_temp_sprite = RM.getSprite("bullet");
	if (!p_temp_sprite) {
		LM.writeLog("Bullet::Bullet(): Warning! Sprite '%s' not found", "bullet");
	}
	else {
		setSprite(p_temp_sprite);
		setSpriteSlowdown(5);
	}

	// Set object type
	setType("Bullet");

	df::Vector p(hero_pos.getX() + 2, hero_pos.getY());
	setPosition(p);

	// Make the bullets soft so can pass through hero
	setSolidness(df::SOFT);
}

int Bullet::eventHandler(const df::Event *p_e) {
	if (p_e->getType() == df::OUT_EVENT) {
		out();
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

// If bullet moves outside world, mark self for deletion
void Bullet::out() {
	WM.markForDelete(this);
}

// If bullet hits Vulture, mark vulture and bullet for deletion
void Bullet::hit(const df::EventCollision *p_collision_event) {
	
	// If Bullet hits Vulture
	if ((p_collision_event->getObject1()->getType() == "Vulture") ||
		(p_collision_event->getObject2()->getType() == "Vulture")) {

		WM.markForDelete(p_collision_event->getObject1());
		WM.markForDelete(p_collision_event->getObject2());

		// Increment score by 50 points
		df::EventView ev("Score", 50, true);
		WM.onEvent(&ev);

	}
}