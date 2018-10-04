The Cowboy Coders - John Amaral, Jarod Thompson
jramaral, jsthompson
Project 3 Alpha

*PLATFORM*

Windows 10, x64, made in Visual Studio

*FILES*
Header files
  * Bandit.h
  * Bullet.h
  * Enemy.h
  * GameOver.h
  * GameStart.h
  * Hero.h
  * Punch.h
  * Reticle.h
  * Vulture.h
Source files
  * Bandit.cpp
  * Bullet.cpp
  * Enemy.cpp
  * game.cpp
  * GameOver.cpp
  * GameStart.cpp
  * Hero.cpp
  * Punch.cpp
  * Reticle.cpp
  * Vulture.cpp
SPRITE FILES
  * bandit-spr.txt
  * bullet-spr.txt
  * gameover-spr.txt
  * gamestart-spr.txt
  * punch-spr.txt
  * sheriff-shooting.txt
  * sheriff-standard.txt
  * vulture-spr.txt
AUDIO FILES
  * bandit-death.wav
  * bandit-first-hit.wav
  * game-over-sound.wav
  * gunshot.wav
  * title-music.wav
  * vulture.hit.wav

*NOTES*

Upon starting the game, the title screen will give instructions (and the title of course), and upon pressing p, the game will start. (Q will quit.) The player is a sheriff in an western
town and must take out all enemies that approach. At first, only Vultures will spawn, and shooting each of them will earn the player 50 points. The player can jump and move along the
horizontal access, but it won't do much at first since the Vultures only spawn in the air.

After 500 points is reached, Bandits will begin to spawn. Unlike the Vultures, they take two hits to kill, but they award twice as many points. The player can also punch enemies as a melee
attack. This of course works better against the Bandits, and will award twice as many points as shooting the pistol.

After 1000 points is reached, an extra life is gained.

The goal (for now) is to last as long as possible and receive as many points as possible. Enemies will infinitely spawn, and the player must survive as long as he or she can. After losing
all lives, the game is over.

The sprites and audio are mostly placeholders for now. The sprites will be more refined and animated in the final version, and the audio samples will be edited for length and volume
balancing.