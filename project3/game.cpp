// game.cpp

/* CREDIT FOR MUSIC AND SOUNDS
 * title-music.wav: limetoe, May 15, 2014, from freesound.org
 * vulture-hit.wav: InspectorJ, February 15, 2018, from freesound.org
 * bandit-hit.wav: AlineAudio, January 28, 2018, from freesound.org
 * bandit-death.wav: AlineAudio, January 28, 2018, from freesound.org
 * gunshot.wav: michorvath, May 6, 2018, from freesound.org
 * game-over-sound.wav: MinigunFiend, January 22, 2013, from freesound.org
 * punch.wav: thefsoundman, April 21, 2011, from freesound.org
 * sheriff-hit.ogg: micahlg, December 10, 2017, from freesound.org
 * sheriff-taunt.wav: shawshank73, July 31, 2011, from freesound.org
 * sheriff-death.wav: AlineAudio, January 27, 2018, from freesound.org
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

	// Load left vulture sprite.
	RM.loadSprite("sprites/vulture-left-spr.txt", "vulture left");

	// Load right vulture sprite.
	RM.loadSprite("sprites/vulture-right-spr.txt", "vulture right");

	// Load sheriff-shooting right sprite.
	RM.loadSprite("sprites/sheriff-shooting-spr.txt", "sheriff right");

	// Load sheriff-shooting left sprite.
	RM.loadSprite("sprites/sheriff-shooting-left-spr.txt", "sheriff left");

	// Load sheriff-standard sprite.
	RM.loadSprite("sprites/sheriff-standard-spr.txt", "sheriff nothing");

	// Load outlaw right sprite.
	RM.loadSprite("sprites/outlaw-right-spr.txt", "outlaw right");

	// Load outlaw left sprite.
	RM.loadSprite("sprites/outlaw-left-spr.txt", "outlaw left");

	// Load bullet sprite.
	RM.loadSprite("sprites/bullet-spr.txt", "bullet");

	// Load explosion sprite.
	RM.loadSprite("sprites/bandit-spr.txt", "bandit");

	// Load game over sprite.
	RM.loadSprite("sprites/gameover-spr.txt", "gameover");

	// Load game start sprite.
	RM.loadSprite("sprites/gamestart-spr.txt", "gamestart");

	// Load punch right sprite
	RM.loadSprite("sprites/punch-spr.txt", "punch right");

	// Load punch left sprite
	RM.loadSprite("sprites/punch-left-spr.txt", "punch left");

	// Load whip right sprite
	RM.loadSprite("sprites/whip-spr.txt", "whip right");

	// Load whip left sprite
	RM.loadSprite("sprites/whip-left-spr.txt", "whip left");

	// Load cactus sprite
	RM.loadSprite("sprites/cactus-spr.txt", "cactus");

	// Load skull sprite
	RM.loadSprite("sprites/skull-spr.txt", "skull");

	// Load sounds
	RM.loadSound("sounds/game-over-sound.wav", "game over");
	RM.loadSound("sounds/vulture-hit.wav", "vulture death");
	RM.loadSound("sounds/bandit-first-hit.wav", "bandit hit");
	RM.loadSound("sounds/bandit-death.wav", "bandit death");
	RM.loadSound("sounds/gunshot.wav", "fire");
	RM.loadSound("sounds/punch.wav", "punch");
	RM.loadSound("sounds/sheriff-hit.ogg", "sheriff hit");
	RM.loadSound("sounds/sheriff-taunt.wav", "sheriff taunt");
	RM.loadSound("sounds/sheriff-death.wav", "sheriff death");

	// Load music tracks
	RM.loadMusic("sounds/title-music.wav", "title music");
}

// Place objects in Game World.
void populateWorld(void) {

	// Spawn GameStart object.
	new GameStart();
}