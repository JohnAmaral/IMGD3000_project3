// GameOver.cpp

// Include statements.
#include "GameOver.h"
#include "ResourceManager.h"
#include "LogManager.h"
#include "EventStep.h"
#include "WorldManager.h"
#include "GameManager.h"
#include "GameStart.h"

// Constructor
GameOver::GameOver() {

	// Initialize background game music.
	g_music = RM.getMusic("game music");

	// Set object type.
	setType("GameOver");

	// Link to "gameover" sprite.
	df::Sprite *p_temp_sprite = RM.getSprite("gameover");
	if (!p_temp_sprite)
		LM.writeLog("GameOver::GameOver(): Warning! Sprite 'gameover' not found");
	else {
		setSprite(p_temp_sprite);
		setSpriteSlowdown(15);

		setTransparency('#');    // Transparent character.

		time_to_live = p_temp_sprite->getFrameCount() * 15;
	}

	// Put message in center of window.
	setLocation(df::CENTER_CENTER);

	// Register for step event.
	registerInterest(df::STEP_EVENT);

	// Pause background game music.
	g_music->stop();

	// Play "game over" sound.
	df::Sound *p_sound = RM.getSound("game over");
	p_sound->play();
}

// Destructor - when object exits, indicate game over.
GameOver::~GameOver() {

	// Remove Saucer and ViewObjects, re-activate GameStart.
	df::ObjectList object_list = WM.getAllObjects(true);
	df::ObjectListIterator i(&object_list);
	for (i.first(); !i.isDone(); i.next()) {
		df::Object *p_o = i.currentObject();
		if (p_o->getType() == "Vulture" || p_o->getType() == "Bandit" || p_o->getType() == "ViewObject")
			WM.markForDelete(p_o); // delete Vultures, Bandits and ViewObjects
		if (p_o->getType() == "GameStart") {
			p_o->setActive(true); // reactive GameStart object
			dynamic_cast <GameStart *> (p_o)->playMusic(); // resume start music
		}
	}
}

// Event handler for Game Over object
int GameOver::eventHandler(const df::Event *p_e) {

	// Step events
	if (p_e->getType() == df::STEP_EVENT) {
		step();
		return 1;
	}
	return 0; // if not step event, ignore
}

// Step method to decrement time_to_live
void GameOver::step() {
	time_to_live--;
	if (time_to_live <= 0) // if game over message done
		WM.markForDelete(this);
}

// Override default draw so as not to display "value".
void GameOver::draw() {
	df::Object::draw();
}