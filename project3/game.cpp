// game.cpp

// Include statements.
#include "GameManager.h"
#include "LogManager.h"
#include "ResourceManager.h"
#include "GameStart.h"
#include "Pause.h"

// Function prototypes.
void loadResources(void);
void populateWorld(void);

int main(int argc, char *argv[]) {

	// Start up game manager.
	if (GM.startUp()) {
		LM.writeLog("Error starting game manager!");
		GM.shutDown();
		return 0;
	}

	// Set flush of logfile during development (when done, make false).
	LM.setFlush(true);

	// Load game resources.
	loadResources();

	// Populate game world with some objects.
	populateWorld();

	// Enable player to pause game.
	new df::Pause(df::Keyboard::F10);

	// Run game.
	GM.run();

	// Shut everything down.
	GM.shutDown();
}

// Load necessary game resources.
void loadResources(void) {

	// Load saucer sprite.
	RM.loadSprite("sprites/vulture-spr.txt", "vulture");

	// Load ship sprite.
	RM.loadSprite("sprites/ship-spr.txt", "sheriff");

	// Load bullet sprite.
	RM.loadSprite("sprites/bullet-spr.txt", "bullet");

	// Load explosion sprite.
	RM.loadSprite("sprites/explosion-spr.txt", "bandit");

	// Load game over sprite.
	RM.loadSprite("sprites/gameover-spr.txt", "gameover");

	// Load game start sprite.
	RM.loadSprite("sprites/gamestart-spr.txt", "gamestart");

	// Load punch sprite
	RM.loadSprite("sprites/punch-spr.txt", "punch");

	// Load sounds
	RM.loadSound("sounds/fire.wav", "fire");
	RM.loadSound("sounds/explode.wav", "explode");
	RM.loadSound("sounds/nuke.wav", "nuke");
	RM.loadSound("sounds/game-over.wav", "game over");

	// Load music tracks
	RM.loadMusic("sounds/start-music.wav", "start music");
	RM.loadMusic("sounds/stargaze.wav", "game music");
}

// Place objects in Game World.
void populateWorld(void) {

	// Spawn GameStart object.
	new GameStart();
}