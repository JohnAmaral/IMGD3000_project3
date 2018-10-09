Brawl of the Buckaroos
The Cowboy Coders - John Amaral, Jarod Thompson
jramaral, jsthompson
Project 3 Final Game

*PLATFORM*

Windows 10, x64, made in Visual Studio

*FILES*
Header files
  * Bandit.h
  * Bullet.h
  * Cactus.h
  * Enemy.h
  * GameOver.h
  * GameStart.h
  * Hero.h
  * Punch.h
  * Reticle.h
  * Skull.h
  * Vulture.h
  * Whip.h
Source files
  * Bandit.cpp
  * Bullet.cpp
  * Cactus.cpp
  * Enemy.cpp
  * game.cpp
  * GameOver.cpp
  * GameStart.cpp
  * Hero.cpp
  * Punch.cpp
  * Reticle.cpp
  * Skull.h
  * Vulture.cpp
  * Whip.cpp
SPRITE FILES
  * bandit-spr.txt
  * bullet-spr.txt
  * cactus-spr.txt
  * gameover-spr.txt
  * gamestart-spr.txt
  * outlaw-left-spr.txt
  * outlaw-right-spr.txt
  * punch-left-spr.txt
  * punch-spr.txt
  * sheriff-shooting-left.txt
  * sheriff-shooting.txt
  * sheriff-standard.txt
  * skull-spr.txt
  * vulture-left-spr.txt
  * vulture-right-spr.txt
  * whip-left-spr.txt
  * whip-spr.txt
  * whip-up-left-spr.txt
  * whip-up-right-spr.txt
AUDIO FILES
  * bandit-death.wav
  * bandit-first-hit.wav
  * game-over-sound.wav
  * gunshot.wav
  * outlaw-taunt.wav
  * punch.wav
  * sheriff-death.wav
  * sheriff-hit.ogg
  * sheriff-taunt.wav
  * title-music.wav
  * vulture.hit.wav
  * whip.wav

*NOTES*

Upon starting the game, the title screen will give instructions (and the title of course). Controls are displayed for both the Sheriff and Outlaw characters. If the player presses 'S',
the Sheriff will be selected and the game will start. If the player presses 'O', the Outlaw will be selected and the game will stat. Pressing Q  will quit the game from the title screen.

The player is either a sheriff in an western town or an outlaw looking for revenge. The player must take out all enemies that approach from the sides of the screen. At first, only Vultures
will spawn, shooting each of them as the Sheriff or hitting them with the Outlaw's whip will earn the player 50 points. The player can jump and move along the horizontal access, but it 
won't do much at first since the Vultures only spawn in the air.

After 250 points is reached, Bandits will begin to spawn. Unlike the Vultures, they take two hits to kill but reward twice as many points. The Sheriff can punch the Bandits for 200 points,
and the Outlaw can whip Bandits for 100 points. For each 250 points earned, more Bandits will be spawned. The number of Bandits to spawn is random and decided from a set range (for the first
range, it is 0 to 2 Bandits). However, with each 1000 points gained, the range increases and makes more Bandits spawn. 

After 1500 points is reached, an extra life is gained.

The goal is to last as long as possible and receive as many points as possible. Enemies will infinitely spawn, and the player must survive as long as he or she can. After losing
all lives, the game is over.