// GameStart.cpp

// Include statements.
#include "GameStart.h"
#include "ResourceManager.h"
#include "LogManager.h"
#include "GameManager.h"
#include "Hero.h"
#include "Vulture.h"
#include "Bandit.h"
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
	t_music = RM.getMusic("title music");
	playMusic();
}

// Play start music.
void GameStart::playMusic() {
	t_music->play();
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

	// Spawn some vultures to kill using loop.
	for (int i = 0; i < 10; i++)
		new Vulture();

	// Spawn some bandits to kill using loop
	//for (int i = 0; i < 3; i++)
		//new Bandit();

	/*// Create display for health count.
	df::ViewObject *p_hc = new df::ViewObject;
	p_hc->setLocation(df::TOP_LEFT); // top left of window
	p_hc->setViewString("Lives");
	p_hc->setValue(5); // initially 6 hit points
	p_hc->setColor(df::RED); // yellow display*/

	/*// Create display for score count.
	df::ViewObject *p_sc = new df::ViewObject;
	p_sc->setLocation(df::TOP_RIGHT); // top right of window
	p_sc->setViewString("Score");
	p_sc->setValue(0); // initially 0 points
	p_sc->setColor(df::GREEN); // green display*/

	

	// Pause start music.
	t_music->stop();

	// When game starts, become inactive.
	setActive(false);
}

// Override default draw so as not to display "value"
void GameStart::draw() {
	df::Object::draw();
}