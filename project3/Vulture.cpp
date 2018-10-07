// Vulture.cpp

// Include statements.
#include "LogManager.h"
#include "WorldManager.h"
#include "ResourceManager.h"
#include "Vulture.h"
#include "EventOut.h"
#include "EventCollision.h"
#include "EventView.h"

// Constructor
Vulture::Vulture() {

	// Set object type.
	setType("Vulture");

	// Set random starting location off right side of screen.
	moveToStart();

	// Set solidness to soft
	setSolidness(df::SOFT);

	// Set transparency
	setTransparency();
}

// Event handler for Vulture objects.
int Vulture::eventHandler(const df::Event *p_e) {

	// Recognizes out-of-bounds event
	if (p_e->getType() == df::OUT_EVENT) {
		out();
		return 1;
	}

	// Collision event
	if (p_e->getType() == df::COLLISION_EVENT) {
		const df::EventCollision *p_collision_event =
			dynamic_cast <const df::EventCollision *> (p_e);
		hit(p_collision_event); // If Vulture collides with another object (for explosions)
		return 1;
	}

	return 0;
}

// Determines if Vulture object is out of bounds.
void Vulture::out() {

	// If x coordinate of Vulture is 0 or less, then out of bounds
	if (getPosition().getX() >= 0)
		return;

	// Otherwise, move Vulture back to right edge of game world
	moveToStart();
}

// Moves Vulture back to start (right edge).
void Vulture::moveToStart() {

	df::Vector temp_pos;

	float world_horiz = WM.getBoundary().getHorizontal(); // horizontal length of game world
	float world_vert = WM.getBoundary().getVertical(); // vertical length of game world

	int rand_spawn = rand() % 100 + 1; // random value between 1 and 100

	if (rand_spawn <= 50) {

		// Setup "vulture right" sprite.
		df::Sprite *p_temp_sprite = RM.getSprite("vulture right");
		if (!p_temp_sprite) // if sprite not found correctly
			LM.writeLog("Vulture::Vulture(): Warning! Sprite '%s' not found", "vulture right");
		else {
			// Setup sprite and set animation to advance once every 4 frames
			setSprite(p_temp_sprite);
			setSpriteSlowdown(4);
		}

		// Set vulture velocity
		setVelocity(df::Vector(-0.25, 0)); // 1 space left every 4 frames

		// x is off right side of window
		temp_pos.setX(world_horiz + rand() % (int)world_horiz + 3.0f); // random x coordinate off right
																	   // side (not in Game World range yet)
		// y is in vertical range
		temp_pos.setY(rand() % (int)(world_vert - 15) + 4.0f); // random y coordinate within Game World range

		// If collision, move right slightly until empty space.
		df::ObjectList collision_list = WM.isCollision(this, temp_pos);
		while (!collision_list.isEmpty()) {
			temp_pos.setX(temp_pos.getX() + 1); // set temp_pos to be 1 space to the right of previous location
			collision_list = WM.isCollision(this, temp_pos); // keep track of position in list
		}
	}
	else if (rand_spawn > 50) {

		// Setup "vulture left" sprite.
		df::Sprite *p_temp_sprite = RM.getSprite("vulture left");
		if (!p_temp_sprite) // if sprite not found correctly
			LM.writeLog("Vulture::Vulture(): Warning! Sprite '%s' not found", "vulture left");
		else {
			// Setup sprite and set animation to advance once every 4 frames
			setSprite(p_temp_sprite);
			setSpriteSlowdown(4);
		}

		// Set vulture velocity
		setVelocity(df::Vector(+0.25, 0)); // 1 space left every 4 frames

		// x is off left side of window
		temp_pos.setX(0 - rand() % (int)world_horiz + 3.0f); // random x coordinate off right
																	   // side (not in Game World range yet)
		// y is in vertical range
		temp_pos.setY(rand() % (int)(world_vert - 15) + 4.0f); // random y coordinate within Game World range

		// If collision, move right slightly until empty space.
		df::ObjectList collision_list = WM.isCollision(this, temp_pos);
		while (!collision_list.isEmpty()) {
			temp_pos.setX(temp_pos.getX() - 1); // set temp_pos to be 1 space to the left of previous location
			collision_list = WM.isCollision(this, temp_pos); // keep track of position in list
		}
	}

	// Move Vulture to random location off left or right side.
	WM.moveObject(this, temp_pos);
}

// Hit method for collisions.
void Vulture::hit(const df::EventCollision *p_collision_event) {

	// If Vulture runs into another Vulture, ignore.
	if ((p_collision_event->getObject1()->getType() == "Vulture") &&
		(p_collision_event->getObject2()->getType() == "Vulture"))
		return; // if both types "Vulture"

	// If Vulture runs into Bullet
	if ((p_collision_event->getObject1()->getType() == "Bullet") ||
		(p_collision_event->getObject2()->getType() == "Bullet")) {

		// Play "vulture death" sound.
		df::Sound *v_sound = RM.getSound("vulture death");
		v_sound->play();

		// Create new Vulture to shoot at.
		new Vulture;
	}
}