// Cactus.cpp

// Includes
#include "Cactus.h"
#include "LogManager.h"
#include "ResourceManager.h"

// Constructor
Cactus::Cactus() {

	// Link to "cactus" sprite.
	df::Sprite *p_temp_sprite;
	p_temp_sprite = RM.getSprite("cactus");
	if (!p_temp_sprite) // "cactus" sprite not found correctly
		LM.writeLog("Cactus::Cactus(): Warning! Sprite '%s' not found", "cactus");
	else {
		setSprite(p_temp_sprite);
		setTransparency();
	}

	// Set altitude to background object
	setAltitude(0);

	// Set type
	setType("Cactus");

	// Set solidness
	setSolidness(df::SPECTRAL);
}