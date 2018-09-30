// GameStart.cpp

// Include statements.
#include "GameStart.h"
#include "ResourceManager.h"
#include "LogManager.h"
#include "GameManager.h"
#include "Hero.h"
#include "Enemy.h"
//#include "Points.h"
#include "Music.h"

// Constructor
GameStart::GameStart() {

	// Set object type.
	setType("GameStart");

	// Put message in center of window.
	setLocation(df::CENTER_CENTER);

	// Link to "gamestart" sprite.
	df::Sprite *p_temp_sprite = RM.getSprite("gamestart");
	if (!p_temp_sprite)
		LM.writeLog("GameStart::GameStart(): Warning! Sprite 'gamestart' not found");
	else {
		setSprite(p_temp_sprite);
		setSpriteSlowdown(15);
	}

	// Register for keyboard events.
	registerInterest(df::KEYBOARD_EVENT);

	// Play start music.
	p_music = RM.getMusic("start music");
	playMusic();

	// Initialize background music, but do not play yet.
	g_music = RM.getMusic("game music");
}

// Play start music.
void GameStart::playMusic() {
	p_music->play();
}

// Event handler for GameStart object.
int GameStart::eventHandler(const df::Event *p_e) {

	// Keyboard events
	if (p_e->getType() == df::KEYBOARD_EVENT) {
		df::EventKeyboard *p_keyboard_event = (df::EventKeyboard *) p_e;

		switch (p_keyboard_event->getKey()) {
			// Press P to play
		case df::Keyboard::P:
			start();
			break;
			// Press Q to quit
		case df::Keyboard::Q:
			GM.setGameOver();
			break;
		default:
			break;
		}
		return 1;
	}
	return 0; // if no keyboard event, ignore
}

// Process of starting game.
void GameStart::start() {

	// Create new Hero object.
	new Hero();

	// Spawn some saucers to shoot using a loop.
	for (int i = 0; i < 15; i++)
		new Enemy();

	// Make Points object - setup heads-up display
	//new Points;

	// Create display for health count.
	df::ViewObject *p_hc = new df::ViewObject;
	p_hc->setLocation(df::TOP_LEFT); // top center of window
	p_hc->setViewString("Health");
	p_hc->setValue(3); // initially 3 hit points
	p_hc->setColor(df::YELLOW); // yellow display

	// Pause start music.
	p_music->pause();

	// Play game music.
	g_music->play();

	// When game starts, become inactive.
	setActive(false);
}

// Override default draw so as not to display "value"
void GameStart::draw() {
	df::Object::draw();
}