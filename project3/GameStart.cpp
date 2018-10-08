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
#include "Cactus.h"

// Constructor
GameStart::GameStart() {

	// Set object type.
	setType("GameStart");

	// Put message in center of window.
	df::Vector p(40, 8);
	setPosition(p);

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
			// Press P to play as the sheriff
		case df::Keyboard::P:
			start(true);
			break;
			// Press L to play as the outlaw
		case df::Keyboard::L:
			start(false);
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
void GameStart::start(bool character_choice) {

	// Create new Hero object.
	new Hero(character_choice);

	// Spawn some vultures to kill using loop.
	for (int i = 0; i < 10; i++)
		new Vulture();

	// Create some cacti
	Cactus *c1 = new Cactus();
	df::Vector pos_1 = c1->getPosition();
	pos_1.setX((float)(rand() % 65 + 10));
	pos_1.setY(20);
	c1->setPosition(pos_1);

	Cactus *c2 = new Cactus();
	df::Vector pos_2 = c2->getPosition();
	pos_2.setX((float)(rand() % 65 + 10));
	pos_2.setY(20);
	c2->setPosition(pos_2);

	// Stop start music.
	t_music->stop();

	// When game starts, become inactive.
	setActive(false);
}

// Override default draw so as not to display "value"
void GameStart::draw() {
	df::Object::draw();
}