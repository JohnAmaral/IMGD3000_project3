// Skull.cpp

// Include statements.
#include "Skull.h"
#include "ResourceManager.h"
#include "LogManager.h"
#include "EventStep.h"
#include "WorldManager.h"

// Constructor
Skull::Skull() {

	// Links to"skull" sprite.
	df::Sprite *p_temp_sprite = RM.getSprite("skull");
	if (!p_temp_sprite) // if sprite not found correctly
		LM.writeLog("Skull::Skull(): Warning! Sprite '%s' not found", "skull");
	else {
		// Setup sprite with no slowdown.
		setSprite(p_temp_sprite);
		setTransparency();
	}

	// Set object type.
	setType("Skull");

	// Set screen time to 10 steps.
	screen_time = 10;

	// Set solidness to Spectral.
	setSolidness(df::SPECTRAL);

	// Register Skull for step events.
	registerInterest(df::STEP_EVENT);
}

// Event handler - handles step events
int Skull::eventHandler(const df::Event *p_e) {

	// Step events
	if (p_e->getType() == df::STEP_EVENT) { // if step event
		step();
		return 1;
	}
	return 0; // if not step event, ignore
}

// Decrements screen_time with each step.
void Skull::step() {

	screen_time--;
	if (screen_time <= 0) // if countdown is 0 (or less), mark Skull for deletion
		WM.markForDelete(this);
}