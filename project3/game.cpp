// game.cpp

/* CREDIT FOR MUSIC AND SOUNDS
 * title-music.wav: limetoe, May 15, 2014, from freesound.org
 * vulture-hit.wav: markb258, August 29, 2014, from freesound.org
 * bandit-hit.wav: AlineAudio, January 28, 2018, from freesound.org
 * bandit-death.wav: AlineAudio, January 28, 2018, from freesound.org
 * gunshot.wav: michorvath, May 6, 2018, from freesound.org
*/

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

	// Load sheriff-shooting sprite.
	RM.loadSprite("sprites/sheriff-shooting-spr.txt", "sheriff gun");

	// Load sheriff-standard sprite.
	RM.loadSprite("sprites/sheriff-standard-spr.txt", "sheriff nothing");

	// Load bullet sprite.
	RM.loadSprite("sprites/bullet-spr.txt", "bullet");

	// Load explosion sprite.
	RM.loadSprite("sprites/bandit-spr.txt", "bandit");

	// Load game over sprite.
	RM.loadSprite("sprites/gameover-spr.txt", "gameover");

	// Load game start sprite.
	RM.loadSprite("sprites/gamestart-spr.txt", "gamestart");

	// Load punch sprite
	RM.loadSprite("sprites/punch-spr.txt", "punch");

	// Load sounds
	RM.loadSound("sounds/nuke.wav", "nuke");
	RM.loadSound("sounds/game-over-sound.wav", "game over");
	RM.loadSound("sounds/vulture-hit.wav", "vulture death");
	RM.loadSound("sounds/bandit-first-hit.wav", "bandit hit");
	RM.loadSound("sounds/bandit-death.wav", "bandit death");
	RM.loadSound("sounds/gunshot.wav", "fire");

	// Load music tracks
	RM.loadMusic("sounds/title-music.wav", "title music");
}

// Place objects in Game World.
void populateWorld(void) {

	// Spawn GameStart object.
	new GameStart();
}