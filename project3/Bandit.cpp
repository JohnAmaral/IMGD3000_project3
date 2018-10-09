// Bandit.cpp

// Include statements.
#include "LogManager.h"
#include "WorldManager.h"
#include "ResourceManager.h"
#include "Bandit.h"
#include "EventOut.h"
#include "EventCollision.h"
#include <stdlib.h> // Used for rand() call in moveToStart()
#include "EventView.h"
#include "Skull.h"

// Constructor
Bandit::Bandit() {

	// Setup "bandit" sprite.
	df::Sprite *p_temp_sprite = RM.getSprite("bandit");
	if (!p_temp_sprite) // if sprite not found correctly
		LM.writeLog("Bandit::Bandit(): Warning! Sprite '%s' not found", "bandit");
	else {
		// Setup sprite and set animation to advance once every 4 frames
		setSprite(p_temp_sprite);
		setSpriteSlowdown(10);
		setTransparency();
	}

	// Initialize attributes
	health_count = 2;

	// Set object type.
	setType("Bandit");

	// Set random starting location off right side of screen.
	moveToStart();

	// Set solidness to soft
	setSolidness(df::SOFT);

	// Set altitude
	setAltitude(1);
}

// Event handler for Bandit objects.
int Bandit::eventHandler(const df::Event *p_e) {

	// Recognizes out-of-bounds event
	if (p_e->getType() == df::OUT_EVENT) {
		out();
		return 1;
	}

	// Collision event
	if (p_e->getType() == df::COLLISION_EVENT) {
		const df::EventCollision *p_collision_event =
			dynamic_cast <const df::EventCollision *> (p_e);
		hit(p_collision_event); // If Bandit collides with another object (for explosions)
		return 1;
	}

	return 0;
}

// Determines if Bandit object is out of bounds.
void Bandit::out() {

	// If x coordinate of Bandit is 0 or less, then out of bounds
	if (getPosition().getX() >= 0)
		return;

	// Otherwise, move Bandit back to right edge of game world
	moveToStart();
}

// Moves Bandit back to start (right edge).
void Bandit::moveToStart() {

	df::Vector temp_pos;

	float world_horiz = WM.getBoundary().getHorizontal(); // horizontal length of game world

	int rand_spawn = rand() % 100 + 1; // random value between 1 and 100

	if (rand_spawn <= 50) { // move right

		// Set Bandit velocity
		setVelocity(df::Vector(-0.25, 0)); // 1 space right every 4 frames

		// x is off right side of window
		temp_pos.setX(world_horiz + rand() % (int)world_horiz + 3.0f); // random x coordinate off right
																	   // side (not in Game World range yet)
		// y is in always on ground with player character
		temp_pos.setY(21);

		// If collision, move right slightly until empty space.
		df::ObjectList collision_list = WM.isCollision(this, temp_pos);
		while (!collision_list.isEmpty()) {
			temp_pos.setX(temp_pos.getX() + 1); // set temp_pos to be 1 space to the right of previous location
			collision_list = WM.isCollision(this, temp_pos); // keep track of position in list
		}
	}
	else if (rand_spawn > 50) {

		// Set Bandit velocity
		setVelocity(df::Vector(+0.25, 0)); // 1 space left every 4 frames

		// x is off left side of window
		temp_pos.setX(0 - rand() % (int)world_horiz + 3.0f); // random x coordinate off left
															// side (not in Game World range yet)
		// y is in vertical range
		temp_pos.setY(21);

		// If collision, move left slightly until empty space.
		df::ObjectList collision_list = WM.isCollision(this, temp_pos);
		while (!collision_list.isEmpty()) {
			temp_pos.setX(temp_pos.getX() - 1); // set temp_pos to be 1 space to the left of previous location
			collision_list = WM.isCollision(this, temp_pos); // keep track of position in list
		}
	}

	// Move Bandit to random location off left or right side.
	WM.moveObject(this, temp_pos);
}

// Hit method for collisions.
void Bandit::hit(const df::EventCollision *p_collision_event) {

	// If Bandit runs into another Bandit, ignore.
	if ((p_collision_event->getObject1()->getType() == "Bandit") &&
		(p_collision_event->getObject2()->getType() == "Bandit"))
		return; // if both types "Bandit"

	// If Bandit runs into Bullet, Whip or Punch
	if ((p_collision_event->getObject1()->getType() == "Bullet") ||
		(p_collision_event->getObject2()->getType() == "Bullet") ||
		(p_collision_event->getObject1()->getType() == "Whip") ||
		(p_collision_event->getObject2()->getType() == "Whip") ||
		(p_collision_event->getObject1()->getType() == "Punch") ||
		(p_collision_event->getObject2()->getType() == "Punch")) {

		if (p_collision_event->getObject1()->getType() == "Whip") {

			bool invincible = dynamic_cast <Whip *> (p_collision_event->getObject1())->isInvincible();
			if (invincible) {
				return;
			}
		}
		if (p_collision_event->getObject2()->getType() == "Whip") {
			bool invincible = dynamic_cast <Whip *> (p_collision_event->getObject2())->isInvincible();
			if (invincible) {
				return;
			}
		}
		if (p_collision_event->getObject1()->getType() == "Punch") {

			bool invincible = dynamic_cast <Punch *> (p_collision_event->getObject1())->isInvincible();
			if (invincible) {
				return;
			}
		}
		if (p_collision_event->getObject2()->getType() == "Punch") {
			bool invincible = dynamic_cast <Punch *> (p_collision_event->getObject2())->isInvincible();
			if (invincible) {
				return;
			}
		}
		

		// Decrement health count by 1
		health_count -= 1;

		if (health_count == 1) {
			// Play "bandit hit" sound.
			df::Sound *b_sound = RM.getSound("bandit hit");
			b_sound->play();
		}

		if (health_count <= 0) {

			// If Bandit collides with Bullet
			if ((p_collision_event->getObject1()->getType() == "Bullet") ||
				(p_collision_event->getObject2()->getType() == "Bullet") ||
				(p_collision_event->getObject1()->getType() == "Whip") ||
				(p_collision_event->getObject2()->getType() == "Whip")) {

				// Increment score by 100 points
				df::EventView ev("Score", 100, true);
				WM.onEvent(&ev);
			}
			// If Bandit collides with Punch or Whip
			if ((p_collision_event->getObject1()->getType() == "Punch") ||
				(p_collision_event->getObject2()->getType() == "Punch")) {

				// Increment score by 200 points
				df::EventView ev("Score", 200, true);
				WM.onEvent(&ev);
			}

			// Mark both objects for deletion
			WM.markForDelete(p_collision_event->getObject1());
			WM.markForDelete(p_collision_event->getObject2());

			// Play "bandit death" sound.
			df::Sound *b_sound = RM.getSound("bandit death");
			b_sound->play();

			// Create Skull icon
			Skull *p_skull = new Skull();
			p_skull->setPosition(this->getPosition());

			return;
		}

		// If bandit didn't die, still need to mark other object for delete
		if ((p_collision_event->getObject1()->getType() == "Bullet") ||
			(p_collision_event->getObject1()->getType() == "Whip") ||
			(p_collision_event->getObject1()->getType() == "Punch"))
			WM.markForDelete(p_collision_event->getObject1());
		if ((p_collision_event->getObject2()->getType() == "Bullet") ||
			(p_collision_event->getObject2()->getType() == "Whip") ||
			(p_collision_event->getObject2()->getType() == "Punch"))
			WM.markForDelete(p_collision_event->getObject2());
	}
}