//
//  level.c
//

#include "level.h"

#include "../utils/fonts.h"
#include "../utils/game_state.h"
#include "../utils/pd_pointer.h"
#include "../utils/rensutils.h"
#include "draw.h"
#include "hazards.h"
#include "physics.h"
#include "player.h"
#include "treasure.h"

static Player player;
int score = 0;
static int heldScore = 0;
static bool zapped = false;

void playTreasureCollectSound(void) {
	static AudioSample *treasureCollectSound;
	static SamplePlayer *treasureCollectSoundPlayer;

	if (treasureCollectSound == NULL || treasureCollectSoundPlayer == NULL) {
		treasureCollectSound = snd->sample->load("sounds/treasure_collect.wav");

		treasureCollectSoundPlayer = snd->sampleplayer->newPlayer();
		snd->sampleplayer->setSample(treasureCollectSoundPlayer, treasureCollectSound);
	}

	snd->sampleplayer->play(treasureCollectSoundPlayer, 1, 1.0);
}

// Main functions

void restartLevel(void) {
	player = newPlayer();
	score = 0;
	regenerateGoldPositions();
	regenerateHazards();
}

void processLevel(float deltaTime) {
	playerMovement(&player, deltaTime);
	processPlayerPhysics(&player, deltaTime);
	processGold(player, &heldScore);
	if (processHazardCollisions(&player)) {
		if (heldScore > 0) {
			zapped = true;
		}
		heldScore = 0;
	}
	if (player.pos.y < WATER_LEVEL && player.pos.y - player.vel.y > WATER_LEVEL) {
		if (heldScore == 0 && zapped) {
			gameState = kGameStateOver;
		}
		if (heldScore > 0) {
			playTreasureCollectSound();
		}

		score += heldScore;
		heldScore = 0;
		zapped = false;
	}
	playerSounds(player);
}

void drawLevel(void) {
	int offsetY = player.pos.y + player.vel.y * 5.0f - 120.0f;
	if (player.pos.y + player.vel.y * 5.0f > FLOOR_LEVEL - LCD_ROWS / 2) {
		offsetY = FLOOR_LEVEL - LCD_ROWS - 2;
	}
	drawWater(offsetY);
	drawGold(offsetY);
	drawHazards(offsetY);
	drawPlayer(player, sys->getCrankAngle(), heldScore);

	drawHUD(player, score);
}