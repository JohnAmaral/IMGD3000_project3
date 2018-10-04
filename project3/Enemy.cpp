// Enemy.cpp

// Include statements.
#include "LogManager.h"
#include "WorldManager.h"
#include "ResourceManager.h"
#include "Enemy.h"
#include "EventOut.h"
#include "EventCollision.h"
#include <stdlib.h> // Used for rand() call in moveToStart()
#include "EventView.h"

// Constructor
Enemy::Enemy() {

	// Set object type.
	setType("Enemy");

	// Set random starting location off side of screen.
	moveToStart();

	// Set solidness to soft
	setSolidness(df::SOFT);
}

// Event handler for Enemy objects.
int Enemy::eventHandler(const df::Event *p_e) {

	// Recognizes out-of-bounds event
	if (p_e->getType() == df::OUT_EVENT) {
		out();
		return 1;
	}

	// Collision event
	if (p_e->getType() == df::COLLISION_EVENT) {
		const df::EventCollision *p_collision_event =
			dynamic_cast <const df::EventCollision *> (p_e);
		hit(p_collision_event); // If Enemy collides with another object (for explosions)
		return 1;
	}

	return 0; // if not out-of-bounds, collision, or Nuke event, ignore
}

// Determines if Enemy object is out of bounds.
void Enemy::out() {

	// If x coordinate of Enemy is 0 or less, then out of bounds
	if (getPosition().getX() >= 0)
		return;

	// Otherwise, move Enemy back to right edge of game world
	moveToStart();
}

// Moves Enemy back to start (right edge).
void Enemy::moveToStart() {

	df::Vector temp_pos;

	float world_horiz = WM.getBoundary().getHorizontal(); // horizontal length of game world
	float world_vert = WM.getBoundary().getVertical(); // vertical length of game world

	int rand_spawn = rand() % 100 + 1; // random value between 1 and 100

	if (rand_spawn <= 50) {

		// Set enemy velocity
		setVelocity(df::Vector(-0.25, 0)); // 1 space right every 4 frames

		// x is off right side of window
		temp_pos.setX(world_horiz + rand() % (int)world_horiz + 3.0f); // random x coordinate off right
																	   // side (not in Game World range yet)
		// y is in vertical range
		temp_pos.setY(rand() % (int)(world_vert - 4) + 4.0f); // random y coordinate within Game World range

		// If collision, move right slightly until empty space.
		df::ObjectList collision_list = WM.isCollision(this, temp_pos);
		while (!collision_list.isEmpty()) {
			temp_pos.setX(temp_pos.getX() + 1); // set temp_pos to be 1 space to the right of previous location
			collision_list = WM.isCollision(this, temp_pos); // keep track of position in list
		}
	}
	else if (rand_spawn > 50) {

		// Set enemy velocity
		setVelocity(df::Vector(+0.25, 0)); // 1 space left every 4 frames

		// x is off left side of window
		temp_pos.setX(0 - rand() % (int)world_horiz + 3.0f); // random x coordinate off right
																	   // side (not in Game World range yet)
		// y is in vertical range
		temp_pos.setY(rand() % (int)(world_vert - 4) + 4.0f); // random y coordinate within Game World range

		// If collision, move right slightly until empty space.
		df::ObjectList collision_list = WM.isCollision(this, temp_pos);
		while (!collision_list.isEmpty()) {
			temp_pos.setX(temp_pos.getX() - 1); // set temp_pos to be 1 space to the left of previous location
			collision_list = WM.isCollision(this, temp_pos); // keep track of position in list
		}
	}

	// Move Enemy to random location off left or right side.
	WM.moveObject(this, temp_pos);
}

// Hit method for collisions.
void Enemy::hit(const df::EventCollision *p_collision_event) {

	// If Enemy runs into another Enemy, ignore.
	if ((p_collision_event->getObject1()->getType() == "Enemy") &&
		(p_collision_event->getObject2()->getType() == "Enemy"))
		return; // if both types "Enemy"

	// If Enemy runs into Bullet
	if ((p_collision_event->getObject1()->getType() == "Bullet") ||
		(p_collision_event->getObject2()->getType() == "Bullet")) {

		// Create new Enemy to shoot at.
		//new Enemy;
	}

	// If Enemy runs into Hero, mark Enemy for deletion.
	if (((p_collision_event->getObject1()->getType()) == "Sheriff") ||
		((p_collision_event->getObject2()->getType()) == "Sheriff")) {

		WM.markForDelete(this);
	}
}